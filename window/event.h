//
// Created by PC on 9/9/2023.
//

#ifndef CUDA_NEU_EVENT_H
#define CUDA_NEU_EVENT_H

#include <functional>
#include <vector>
#include <future>


using TouchEventType = std::function<void(int, int)>;


class Event {

private:
    TouchEventType TouchEventChain = nullptr;


    std::vector<std::future<void>> tasks_;
    std::mutex mutex_;
//
//    Event *children;
//    int childCount;

public:

    template<typename Func, typename... Args>
    void addAsyncTask(Func &&func, Args &&... args);

    void awaitAll();


    void addTouchEvent(TouchEventType callBack);

    void dispatchTouchEvent(int x, int y);


protected:
    Event();

    template<typename ChainFuncType>
    void addChainFunction(ChainFuncType &chainFunc, ChainFuncType callBack, bool callAsync = true);
    template<typename ChainFunc, typename... Args>
    void dispatchChainFunction(ChainFunc &chainFunc, Args &&... args);

};


#endif //CUDA_NEU_EVENT_H
