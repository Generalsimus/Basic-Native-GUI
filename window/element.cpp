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


template<typename ChainFuncType>
void Element::addChainFunction(ChainFuncType &chainFunc, ChainFuncType callBack, bool callAsync) {

    if (chainFunc == nullptr) {
        if (callAsync) {
            chainFunc = [callBack]<typename... Args>(Args &&... args) {
                callBack(std::forward<Args>(args)...);
            };
        } else {
            chainFunc = std::move(callBack);
        }
    } else {
        auto currentTouchEventChain = std::move(chainFunc);
        if (callAsync) {
            chainFunc = [currentTouchEventChain, callBack]<typename... Args>(Args &&... args) {
                currentTouchEventChain(std::forward<Args>(args)...);
                callBack(std::forward<Args>(args)...);
            };
        } else {
            auto self = this;
            chainFunc = [currentTouchEventChain, callBack, &self]<typename... Args>(Args &&... args) {
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

    addChainFunction(TouchEventChain, firstCallBack);
    return addTouchEvent(rest...);
}


void Element::dispatchTouchEvent(int windowX, int windowY) {
    printf("RUN dispatchTouchEvent() X:%d \n", windowX);
    if ((windowX > this->x) && (windowX < (this->x + this->width)) && (windowY > this->y) &&
        (windowY < (this->y + this->height))) {
        dispatchChainFunction(TouchEventChain, this, windowX, windowY);

        for (auto &child: children) {
            child->dispatchTouchEvent(windowX, windowY);
        }
    }

}


template<typename Func, typename... Args>
void Element::addAsyncTask(Func &&func, Args &&... args) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.emplace_back(std::async(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...));
}

void Element::awaitAll() {
    for (auto &task: tasks_) {
        task.wait();
    }
}

//using TouchEventType = std::function<void(Element *, int, int)>;
//template<typename... Args>
//auto CreateEvent() {
//    return []() {
//        std::function<void(Args &&...)> eventChainFunc = nullptr;
//    }
//}
//

template<typename CallBackFunc, typename... Args>
Element* Element::addEvent(const std::string &name, CallBackFunc callBack) {
    printf("\nRUN addEvent()\n");

//    using EventListener = void (*)(std::any &);
    EventListenerType<Args...> newss = callBack;
//    events[name] = callBack;
//    auto refValue = events[name];
//    CallBackFunc newChain = std::any_cast<CallBackFunc>(refValue);
    if (events.find(name) == events.end()) {
        printf("\nRUN RRRRRRRRR()\n");

        //  newChain = std::any_cast<CallBackFunc>(events[name]);
        //  newChain = nullptr;
//
//      addChainFunction(newChain, callBack, true);
//        events[name] = callBack;
    } else {
        printf("\nRUN EEEEEEEEEEEEEEE()\n");
        // printf("\nRUN EEEEEEEEEEE()\n");
        // std::function<ReturnType(Args &&...)> newChain = nullptr;
//         = std::any_cast<CallBackFunc>(events[name]);

        // addChainFunction(newChain, callBack, true);
//        events[name] = newChain;
    }
//    events[name] = newChain;
    return this;
}

template<typename... Args>
void Element::dispatchEvent(const std::string &name, Args &&... args) {
    printf("\nRUN dispatchEvent()\n");
//    (std::any_cast<std::function<void(Element *, Args &&...)>>(events[name]))(this, std::forward<Args>(args)...);
    auto eventFunction = std::any_cast<std::function<void(Element *, Args &&...)>>((events[name]));
    printf("\nRUN 22222222222222()\n");
    eventFunction(this, std::forward<Args>(args)...);
//    CallBackFunc ss = events[name];
}