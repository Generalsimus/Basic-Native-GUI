//
// Created by PC on 9/9/2023.
//

#include "event.h"
#include "./utils.cpp"


void Event::addTouchEvent(TouchEventType callBack) {
    printf("addTouchEvent\n");
    if (TouchEventChain == nullptr) {
        TouchEventChain = &callBack;
        dispatchTouchEvent(2, 4);
    } else {
        // CreateFunctionChain(TouchEventChain, callBack);
    }
}

void Event::dispatchTouchEvent(int x, int y) {
    printf("\ndispatchTouchEvent(x: %d, y: %d)  \n", x, y);
    if (TouchEventChain != nullptr) {
        printf("IN IF (x: %d, y: %d)  \n", x, y);
        (*TouchEventChain)(1, 5);
        printf("dispatchTouchEvent(x: %d, y: %d) ddd \n", x, y);
    };
    printf("dispatchTouchEvent(x: %d, y: %d) 2 \n", x, y);
}

Event::Event() {
    printf("\nRUN Event\n");

}

template<typename CallAsyncFunc>
void Event::asyncCall(CallAsyncFunc callAsync) {
    printf("RUN asyncCall()\n");;
    std::async(std::launch::async, callAsync);
//    this->asyncProcesses.push_back(std::async(std::launch::async, callAsync));
    printf("RUN asyncCall() 222222\n");
}

void Event::awaitAll() {
    for (auto &asyncProces: this->asyncProcesses) {
        asyncProces.get();
    }
}
