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
    TouchEventType* TouchEventChain = nullptr;

    std::vector <std::future<void>> asyncProcesses;


public:


    void addTouchEvent(TouchEventType callBack);
    void dispatchTouchEvent(int x, int y);




protected:
    Event();

    template<typename CallAsyncFunc>
    void asyncCall(CallAsyncFunc callAsync);

    void awaitAll();

};


#endif //CUDA_NEU_EVENT_H
