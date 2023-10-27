#include <mutex>
#include <thread>
#include <functional>

std::mutex vectorMutex;
std::vector<std::thread> *_threads = new std::vector<std::thread>();


unsigned int maxThreadLimit = std::thread::hardware_concurrency();
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
//    std::unique_lock<std::mutex> mutexLock(vectorMutex);

    vectorMutex.lock();

//    _threads->emplace_back(func, std::forward<Args>(args)...);
    _threads->push_back(std::thread(func, std::forward<Args>(args)...));
//    _threads->emplace_back([returnValue, func, args...]() mutable {
//          func(std::forward<Args>(args)...);
//    });

//    printf("\nPROCESSS RUN AT Id: %zu\n", _threads->at(_threads->size() - 1).get_id());

    vectorMutex.unlock();
};

// std::mutex awaitAllAsyncTasksMutex;
void awaitAllAsyncTasks() {

    while (!_threads->empty()) {
        vectorMutex.lock();
        std::thread &threadProcess = _threads->front();
        vectorMutex.unlock();

        if (threadProcess.joinable()) {
            threadProcess.join();
        }
    };

    delete _threads;
};


auto CreateAsyncAwaitGroup() {
    vectorMutex.lock();
    std::vector<std::thread> *_savedThreads = _threads;

    std::vector<std::thread> *_newThreads = new std::vector<std::thread>();
    _threads = _newThreads;
    vectorMutex.unlock();

    return [_newThreads, _savedThreads]() {
        vectorMutex.lock();
        _threads = _savedThreads;
        vectorMutex.unlock();

        for (auto &thread: *_newThreads) {
            if (thread.joinable()) {
                thread.join();
            }
        };

        delete _newThreads;
    };
}