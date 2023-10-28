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
thread_local std::vector<std::thread> _threads;
unsigned int maxThreadLimit = std::thread::hardware_concurrency();

//TESSS testworket();
//
//template<typename Ret, typename... Args> auto runAwaitAsyncTask(std::function < Ret(Args && ...) > && func, Args && ...
//args) {
//
//Ret returnValue;
//
//_threads.emplace_back([returnValue, func, args...]() mutable {
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
//    std::unique_lock<std::mutex> mutexLock(vectorMutex);

//    vectorMutex.lock();
//    std::unique_lock<std::mutex> mutexLock(vectorMutex);
//    _threads.emplace_back(func, std::forward<Args>(args)...);
//    _threads.push_back(std::thread(func, std::forward<Args>(args)...));
    _threads.push_back(std::thread([func, args...]() mutable {
        std::cout << "THREAD RUn" << std::endl;
        func(std::forward<Args>(args)...);
        for (auto &thread: _threads) {
            if (thread.joinable()) {
                thread.join();
            }
        };

        _threads.clear();
    }));
//    _threads.emplace_back([func, args...]() mutable {
//        func(std::forward<Args>(args)...);
//        for (auto &thread: *_threads) {
//            if (thread.joinable()) {
//                thread.join();
//            }
//        };
//        delete _threads;
//    });

//    printf("\nPROCESSS RUN AT Id: %zu\n", _threads.at(_threads.size() - 1).get_id());

//    mutexLock.unlock();
};

// std::mutex awaitAllAsyncTasksMutex;
void awaitAllAsyncTasks() {
    while(true){

    }
    while(!_threads.empty()) {
        std::thread &threadProcess = *_threads.begin();

        if (threadProcess.joinable()) {
            threadProcess.join();
        }
        _threads.erase(_threads.begin());
    };

//    delete _threads;
};


auto CreateAsyncAwaitGroup() {
    int startIndex = _threads.size();

    return [startIndex]() {
//        return;
        std::vector<std::thread>::iterator start = _threads.begin() + startIndex;
        std::vector<std::thread>::iterator end = _threads.end();

        while (start != end) {
            std::thread &threadProcess = *start;

            if (threadProcess.joinable()) {
                threadProcess.join();
                _threads.erase(start);
            }
            start++;
        };
    };
}