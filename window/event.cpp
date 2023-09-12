//
// Created by PC on 9/9/2023.
//

#include "event.h"
#include "./utils.cpp"
#include <vector>
#include <future>


void Event::addTouchEvent(TouchEventType callBack) {
    printf("addTouchEvent\n");
    if (TouchEventChain == nullptr) {
       // TouchEventChain = &callBack;
       // dispatchTouchEvent(2, 4);
    } else {
        // CreateFunctionChain(TouchEventChain, callBack);
    }
}

void Event::dispatchTouchEvent(int x, int y) {
    printf("\ndispatchTouchEvent(x: %d, y: %d)  \n", x, y);
    if (TouchEventChain != nullptr) {
        printf("IN IF (x: %d, y: %d)  \n", x, y);
        //(*TouchEventChain)(1, 5);
        printf("dispatchTouchEvent(x: %d, y: %d) ddd \n", x, y);
    };
    printf("dispatchTouchEvent(x: %d, y: %d) 2 \n", x, y);
}

Event::Event() {
    printf("\nRUN Event\n");

    printf("\nRUN Eventeee\n");

}





template<typename Func, typename... Args>
void Event::addAsyncTask(Func&& func, Args&&... args) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.emplace_back(std::async(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...));
}

void Event::awaitAll() {
    for (auto& task : tasks_) {
        task.wait();
    }
}
