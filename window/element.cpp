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
        if (callAsync) {
//            auto currentTouchEventChain = std::function(callBack);
            chainFunc = [&callBack, &self]<typename... Args>(Args... args) {
//                callBack(std::forward<Args>(args)...);
                self->addAsyncTask(callBack, std::forward<Args>(args)...);
            };
        } else {
            chainFunc = std::move(callBack);
        }
    } else {
        auto currentTouchEventChain = std::move(chainFunc);
        if (callAsync) {
            chainFunc = [currentTouchEventChain, callBack]<typename... Args>(Args ... args) {
                currentTouchEventChain(std::forward<Args>(args)...);
                callBack(std::forward<Args>(args)...);
            };
        } else {
            chainFunc = [currentTouchEventChain, callBack, &self]<typename... Args>(Args... args) {
                currentTouchEventChain(std::forward<Args>(args)...);
                self->addAsyncTask(callBack, std::forward<Args>(args)...);
            };
        }
    }

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

//    addChainFunction(TouchEventChain, firstCallBack);
    return addTouchEvent(rest...);
}


void Element::dispatchTouchEvent(int windowX, int windowY) {
    printf("RUN dispatchTouchEvent() X:%d \n", windowX);
    if ((windowX > this->x) && (windowX < (this->x + this->width)) && (windowY > this->y) &&
        (windowY < (this->y + this->height))) {
//        dispatchChainFunction(TouchEventChain, this, windowX, windowY);

        for (auto &child: children) {
            child->dispatchTouchEvent(windowX, windowY);
        }
    }

}


template<class Func, typename... Args>
void Element::addAsyncTask(Func &&func, Args ... args) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.emplace_back(std::async(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...));
}

void Element::awaitAll() {
    for (auto &task: tasks_) {
        task.wait();
    }
}

#include <functional>

template<typename ...Args>
auto FUCRR(std::function<void(Args...)> ss) {
    return ss;
}

//int main()
//{
//    foo([](int, int) { return true; });
//}
template<typename CallBackFunc>
Element *Element::addEvent(const std::string &name, const CallBackFunc &callBack, bool callAsync) {
    printf("\nRUN addEvent()\n");
//
    if (auto eventCallBack = events.find(name); eventCallBack != events.end()) {
        printf("\nRUN addEvent IF()\n");
//        auto callBackFn = std::function(callBack);
//        auto newChain = std::any_cast<decltype(callBackFn)>(eventCallBack->second);
//
//        addChainFunction(newChain, std::function(callBack), false, callAsync);
//        this->events.emplace(name, std::any(newChain));

    } else {
        printf("\nRUN addEvent ELSE()\n");

        auto callBackFn = std::function(callBack);
//        auto newChain = std::function(callBack);
//        auto newChain =  std::function(callBack);
        decltype(callBackFn) newChain = nullptr;
        addChainFunction(newChain, std::function(callBack), true, callAsync);
        this->events.emplace(name, std::any(newChain));

    }
    printf("\nRUN addEvent ENT()\n");
    return this;
}

template<class... Args>
Element *Element::dispatchEvent(const std::string &name, Args &&... args) {
    printf("\nRUN dispatchEvent() \n");

//    auto eventCallBack = events.find(name);
//    std::any_cast<std::function<void(Element *, Args...)>>(eventCallBack->second)(this,
//                                                                                  std::forward<Args>(args)...);
    if (auto eventCallBack = events.find(name); eventCallBack != events.end()) {

        try {
            std::any_cast<std::function<void(Element *, Args...)>>(eventCallBack->second)(this,
                                                                                          std::forward<Args>(args)...);
        }
        catch (const std::bad_any_cast &e) {
            std::cout << "EVENT PASSED WRONG ARGUMENTS" << std::endl;
        }
    } else {
        std::cout << "EVENT NOT EXISTS" << std::endl;
    }


    printf("\nRUN YYYYYYYYYYYYYYYYYY()\n");

    return this;
}