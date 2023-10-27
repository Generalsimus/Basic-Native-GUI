#include <mutex>
#include <thread>
#include <functional>

std::mutex vectorMutex;
std::vector<std::thread> _threads;

unsigned int maxThreadLimit = std::thread::hardware_concurrency();

template<typename Ret, typename... Args> auto runAwaitAsyncTask(std::function < Ret(Args && ...) > && func, Args && ...
args) {

Ret returnValue;

_threads.emplace_back([returnValue, func, args...]() mutable {
returnValue = func(std::forward<Args>(args)...);
});

return [returnValue]() mutable -> Ret {
return
returnValue;
};
}

template<typename Func, typename... Args>
void runAsyncTask(Func &&func, Args &&...args) {
    std::unique_lock<std::mutex> mutexLock(vectorMutex);


//    _threads.emplace_back(func, std::forward<Args>(args)...);
    _threads.push_back(std::thread(func, std::forward<Args>(args)...));
//    _threads.emplace_back([returnValue, func, args...]() mutable {
//          func(std::forward<Args>(args)...);
//    });

//    printf("\nPROCESSS RUN AT Id: %zu\n", _threads.at(_threads.size() - 1).get_id());

    mutexLock.unlock();
};

// std::mutex awaitAllAsyncTasksMutex;
void awaitAllAsyncTasks() {
    //    std::unique_lock<std::mutex> mutexLock(vectorMutex);
    //  std::scoped_lock<std::mutex> mutexLock(vectorMutex);
    //  std::lock_guard<std::mutex> mutexLock(vectorMutex);
    //    auto mutexLock = vectorMutex;

//    vectorMutex.lock();
    while (true) {}
    std::unique_lock<std::mutex> mutexLock(vectorMutex);
    while (_threads.empty()) {
        std::thread &threadProcess = *_threads.begin();
        if (threadProcess.joinable()) {
            printf("\nPROCESSS END JOINABLE Id: %zu\n", threadProcess.get_id());

            mutexLock.unlock();
            threadProcess.join();
            mutexLock = std::unique_lock<std::mutex>(vectorMutex);

            _threads.erase(_threads.begin());
        } else {
            printf("\nPROCESSS END NOT JOINABLE Id: %zu\n", threadProcess.get_id());
            _threads.erase(_threads.begin());
        }
        //    mutexLock.unlock();
    };

    _threads.clear();
    mutexLock.unlock();
};

auto RemoveThreadsBetweenIterator(std::vector<std::thread>::iterator startIterator,
                                  std::vector<std::thread>::iterator endIterator) {
    std::cout << "INDEX STARTITERATO: " << std::distance(_threads.begin(), startIterator) << std::endl;
    std::cout << "INDEX ENDITERATOR: " << std::distance(_threads.begin(), endIterator) << std::endl;

    auto mutexLock = std::unique_lock<std::mutex>(vectorMutex);


    while (true) {
        std::cout << "INDEX RUN PROCESS: " << std::distance(_threads.begin(), endIterator) << std::endl;
        std::thread &threadProcess = *endIterator;
        if (threadProcess.joinable()) {
//            mutexLock.unlock();
            threadProcess.join();
//            mutexLock = std::unique_lock<std::mutex>(vectorMutex);
            _threads.erase(endIterator);

        }
        if (startIterator == endIterator) { break; };
        --endIterator;
    }

    mutexLock.unlock();
}

auto CreateAsyncAwaitGroup() {
    std::unique_lock<std::mutex> mutexLock(vectorMutex);
    std::vector<std::thread>::iterator start = _threads.back();


    std::vector<std::thread> _threads;
    std::vector<std::thread> _threads;

    int startIndex = _threads.size();

    mutexLock.unlock();

//    std::cout << "INDEX START BEFORE MOVE: " << std::distance(_threads.begin(), start) << "\n \n \n" << std::endl;
    return [start, startIndex]() mutable {
        if (_threads.empty()) { return; };
        auto mutexLock = std::unique_lock<std::mutex>(vectorMutex);

        std::cout << "THREADS SIZE WHEN START: " << _threads.size() << std::endl;
        std::vector<std::thread>::iterator end = _threads.back();
//        if (start == end) { return; };

        if (startIndex == 0) {
            start = start.front();
        } else {
            start = start + 1;
        }
//        if (start == nullptr) {
//            start = start.front();
//        } else {
//            start = start + 1;
//        }

//        if (start != end) {
//            start = start + 1;
//        };


        mutexLock.unlock();

        if (start != end) {
            std::cout << "START INDEX: " << startIndex << std::endl;
            std::cout << "INDEX START: " << std::distance(_threads.begin(), start) << std::endl;
            std::cout << "INDEX END: " << std::distance(_threads.begin(), end) << std::endl;
            RemoveThreadsBetweenIterator(start, end);

        };
//        if (_threads.empty()) {
//            return;
//        } else {
//            end--;
//        }
//        if (start != end) {
//            if (start == _threads.begin()) {
//                RemoveThreadsBetweenIterator(start, end - 1);
//            } else {
//                RemoveThreadsBetweenIterator(start - 1, end - 1);
//            }
//        }
        if (startIndex == 0) {
            if (!_threads.empty()) {
                RemoveThreadsBetweenIterator(_threads.begin(), end - 1);
            }
        } else {
            RemoveThreadsBetweenIterator(start - 1, end - 1);
        }
        std::cout << "THREADS SIZE WHEN END: " << _threads.size() << "\n \n \n" << std::endl;
//
//        std::vector<std::thread>::iterator end = _threads.end();
//
//        if ((start + 1) == end) {
//            return;
//        };
//
//        std::cout << "INDEX START: " << std::distance(_threads.begin(), start) << "\n" << std::endl;
//        std::cout << "INDEX END: " << std::distance(_threads.begin(), end) << "\n" << std::endl;
//        return;
//
//
//        while (start != end) {
//
//            std::cout << "PROCESS INDEX: " << std::distance(_threads.begin(), end) << "\n" << std::endl;
//
//            std::thread threadProcess = std::move(*end);
//            if (threadProcess.joinable()) {
//                mutexLock.unlock();
//                threadProcess.join();
//                mutexLock = std::unique_lock<std::mutex>(vectorMutex);
//                _threads.erase(end);
//                end--;
//            }
//        }
//        mutexLock.unlock();

//        std::cout << "startIndex: "<< startIndex << std::endl;
//        std::vector<int>::iterator lastIterator;
//        //    return;
//        std::unique_lock<std::mutex> mutexLock(vectorMutex);
//        int endIndex = _threads.size();
//        std::cout << "endIndex: "<< endIndex << std::endl;
//
//        //    int size = _threads.size();y
//        //    int size2 = startIndex;
//        while (startIndex != endIndex && startIndex < _threads.size()) {
//
//            printf("startIndexE: %zu, endIndex: %zu, size: %zu\n ", startIndex, endIndex, _threads.size());
//            std::thread &threadProcess = _threads.at(startIndex);
//            //
//            if (threadProcess.joinable()) {
//                _threads.erase(_threads.begin() + startIndex);
//
//                mutexLock.unlock();
//                threadProcess.join();
//                mutexLock.lock();
//            } else {
//                _threads.erase(_threads.begin() + startIndex);
//            };
//            endIndex--;
//        };
//        std::cout << "Real endIndex: "<< _threads.size() << std::endl;
//        mutexLock.unlock();
//        printf("END SIZE: %zu\n ", _threads.size());
    };
}