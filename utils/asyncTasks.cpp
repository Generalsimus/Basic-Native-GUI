#include <thread>
//#include <functional>
//#include <iostream>
//#include <cstdlib> // Include for atexit

//class TESSS {
//    ~TESSS() {
//        std::cout << "EJECT TEST OK " << std::endl;
//    }
//};
//std::mutex vectorMutex;
thread_local std::vector<std::thread> *_threads = new std::vector<std::thread>();
unsigned int maxThreadLimit = std::thread::hardware_concurrency();

//TESSS testworket();
//
//template<typename Ret, typename... Args> auto runAwaitAsyncTask(std::function < Ret(Args && ...) > && func, Args && ...
//args) {
//
//Ret returnValue;
//
//_threads->emplace_back([returnValue, func, args...]() mutable {
//returnValue = func(std::forward<Args>(args)...);
//});
//
//return [returnValue]() mutable -> Ret {
//return
//returnValue;
//};
//}

template<typename Func, typename... Args>
void runAsyncTask(Func &&func, Args &&...args) {

    _threads->push_back(std::thread([func, args...]() mutable {
        func(std::forward<Args>(args)...);
        for (auto &thread: *_threads) {
            if (thread.joinable()) {
                thread.join();
            }
        };

        delete _threads;
//        _threads->clear();
    }));

};


void awaitAllAsyncTasks() {
    while (!_threads->empty()) {
        std::thread &threadProcess = *_threads->begin();

        if (threadProcess.joinable()) {
            threadProcess.join();
            _threads->erase(_threads->begin());
        }
    };

    delete _threads;
};


auto CreateAsyncAwaitGroup() {
    std::vector<std::thread> *_savedThreads = _threads;
    std::vector<std::thread> *_newThreads = new std::vector<std::thread>();
    _threads = _newThreads;

    return [_savedThreads, _newThreads]() {
        _threads = _savedThreads;

        for (auto &thread: *_newThreads) {
            if (thread.joinable()) {
                thread.join();
            }
        };

        delete _newThreads;
    };
}