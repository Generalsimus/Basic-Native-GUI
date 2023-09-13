//
// Created by PC on 9/9/2023.
//

#include "event.h"
#include <vector>
#include <future>

template<typename ChainFuncType>
void Event::addChainFunction(ChainFuncType &chainFunc, ChainFuncType callBack, bool callAsync) {

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
void Event::dispatchChainFunction(ChainFunc &chainFunc, Args &&... args) {
    if (chainFunc != nullptr) {
        chainFunc(std::forward<Args>(args)...);
    };
}

void Event::addTouchEvent(TouchEventType callBack) {
    addChainFunction(TouchEventChain, callBack);
}

void Event::dispatchTouchEvent(int x, int y) {
    dispatchChainFunction(TouchEventChain, x, y);
}

Event::Event() {
    printf("\nRUN Event\n");

    printf("\nRUN Eventeee\n");
}


template<typename Func, typename... Args>
void Event::addAsyncTask(Func &&func, Args &&... args) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.emplace_back(std::async(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...));
}

void Event::awaitAll() {
    for (auto &task: tasks_) {
        task.wait();
    }
}