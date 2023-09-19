//
// Created by PC on 9/3/2023.
//

#include "element.h"
#include "./utils.cpp"

Element *Element::addChildElement() {
    return this;
};

template<typename... Chi>
Element *Element::addChildElement(Element *child, Chi... rest) {
    printf("RUN addChildElement\n");


    this->children.push_back(child);

    child->parent = this;

    return this->addChildElement(rest...);
};

Element *Element::addDrawStyles() {
    /* DrawChainType currentChain = this->drawChain;

       this->drawChain = [currentChain, callBackStyleChain](Element * el, Window* win) {
           currentChain(el, win);
           callBackStyleChain(el, win);
       };*/

    return this;
}

Element::Element() : x(0), y(0) {
    printf("RUN Element() NO CHILD\n");

    //std::vector<std::future<void>> tasks;
//    tasks_ = tasks;

};

template<typename... Args>
Element::Element(Element *first, Args... rest):x(0), y(0) {
    printf("RUN Element() WITH CHILD\n");

    addChildElement(first);
    addChildElement(rest...);
}


template<typename CallBackFunction>
void Element::addChainFunction(CallBackFunction &chainFunc, CallBackFunction callBack, bool startFromNewPoint,
                               bool callAsync) {
    printf("\nRUN addChainFunction()\n");


    auto self = this;
    if (startFromNewPoint) {
//        auto currentCallBack = std::move(callBack);
        if (callAsync) {
            chainFunc = [callBack, &self]<typename... Args>(Args ... args) {
//                std::unique_lock<std::mutex> lock(self->mutex_);
//                currentCallBack(std::forward<Args>(args)...);
                self->addAsyncTask(callBack, std::forward<Args>(args)...);
//                self->tasks_.emplace_back(std::async(std::launch::async, callBack, std::forward<Args>(args)...));
            };
        } else {
//            chainFunc = std::move(callBack);
            chainFunc = std::move(callBack);
        }
    } else {
        auto currentChainFunc = std::move(chainFunc);


        auto currentCallBack =std::forward<CallBackFunction>(callBack);
//                std::move(callBack);
        if (callAsync) {
            chainFunc = [currentChainFunc, currentCallBack, &self]<typename... Args>(Args  ... args) {
                currentChainFunc(std::forward<Args>(args)...);
//                callBack(std::forward<Args>(args)...);
//                std::lock_guard<std::mutex> lock(self- >mutex_);
//.std::forward<CallBackFunction>(callBack)
                self->addAsyncTask(currentCallBack, std::forward<Args>(args)...);
//                self->tasks_.emplace_back(std::async(std::launch::async, callBack, std::forward<Args>(args)...));
            };
        } else {
            chainFunc = [currentChainFunc, callBack]<typename... Args>(Args &&... args) {
                currentChainFunc(std::forward<Args>(args)...);
                callBack(std::forward<Args>(args)...);
            };

        }
    }
    return;
//    if (startFromNewPoint) {
//        if (callAsync) {
//            chainFunc = [&callBack, &self]<typename... Args>(Args &&... args) {
////                callBack(std::forward<Args>(args)...);
//                self->addAsyncTask(callBack, std::forward<Args>(args)...);
//            };
//        } else {
//            chainFunc = std::move(callBack);
//        }
//    } else {
//        auto currentTouchEventChain = std::move(chainFunc);
//        if (callAsync) {
//            chainFunc = [currentTouchEventChain, callBack]<typename... Args>(Args &&... args) {
//                currentTouchEventChain(std::forward<Args>(args)...);
//                callBack(std::forward<Args>(args)...);
//            };
//        } else {
//            chainFunc = [currentTouchEventChain, callBack, &self]<typename... Args>(Args &&... args) {
//                currentTouchEventChain(std::forward<Args>(args)...);
//                self->addAsyncTask(callBack, std::forward<Args>(args)...);
//            };
//        }
//    }

}


template<typename ChainFunc, typename... Args>
void Element::dispatchChainFunction(ChainFunc &chainFunc, Args &&... args) {
    if (chainFunc != nullptr) {
        chainFunc(std::forward<Args>(args)...);
    };
}


Element *Element::addTouchEvent() {
    return this;
};

template<typename... Args>
Element *Element::addTouchEvent(TouchEventType firstCallBack, Args... rest) {
    printf("RUN Element() WITH CHILD\n");

    addChainFunction(TouchEventChain, firstCallBack, TouchEventChain == nullptr, true);
    return this;
    return addTouchEvent(rest...);
}


void Element::dispatchTouchEvent(int windowX, int windowY) {
    printf("RUN dispatchTouchEvent() X:%d \n", windowX);
//    if ((windowX > this->x) && (windowX < (this->x + this->width)) && (windowY > this->y) &&
//        (windowY < (this->y + this->height))) {
    dispatchChainFunction(TouchEventChain, this, windowX, windowY);

//        for (auto &child: children) {
//            child->dispatchTouchEvent(windowX, windowY);
//        }
//    }

}


template<typename Func, typename... Args>
void Element::addAsyncTask(Func &&func, Args &&... args) {
//    std::lock_guard<std::mutex> lock(mutex_);
//    self->tasks_.emplace_back(std::async(std::launch::async, func, std::forward<Args>(args)...));
    this->tasks_.emplace_back(std::async(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...));
}


void Element::awaitAll() {
    for (auto &task: tasks_) {
        task.wait();
    }
}