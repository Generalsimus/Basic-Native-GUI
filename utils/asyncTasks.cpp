
#include <mutex>
#include <thread>

std::mutex vectorMutex;
std::vector<std::thread> _threads;

unsigned int maxThreadLimit = std::thread::hardware_concurrency();

template <typename Func, typename... Args>
auto runAsyncTask(Func &&func, Args &&...args) {
  //  vectorMutex.lock();

  std::unique_lock<std::mutex> mutexLock(vectorMutex);

  _threads.emplace_back([&func, args...]() {
        func(args...);
  });

  printf("\nPROCESSS RUN AT Id: %zu\n",
         _threads.at(_threads.size() - 1).get_id());
  mutexLock.unlock();

  return []() {
    //        _awaitTasksList.at(threadIndex)();
    //    if (threadPtr->joinable()) {
    //      threadPtr->join();
    //    }
    //    currentThread->join();
    //    return *returnValue;
  };
};

// std::mutex awaitAllAsyncTasksMutex;
void awaitAllAsyncTasks() {
  //    std::unique_lock<std::mutex> mutexLock(vectorMutex);
  //  std::scoped_lock<std::mutex> mutexLock(vectorMutex);
  //  std::lock_guard<std::mutex> mutexLock(vectorMutex);
  //    auto mutexLock = vectorMutex;

  vectorMutex.lock();

  while (_threads.size() != 0) {
    //    std::unique_lock<std::mutex> mutexLock(vectorMutex);
    std::thread threadProcess = std::move(*_threads.begin());
    if (threadProcess.joinable()) {
      _threads.erase(_threads.begin());

      printf("\nPROCESSS END JOINABLE Id: %zu\n", threadProcess.get_id());

      vectorMutex.unlock();
      threadProcess.join();
      vectorMutex.lock();
    } else {
      printf("\nPROCESSS END NOT JOINABLE Id: %zu\n", threadProcess.get_id());
      _threads.erase(_threads.begin());
    }
    //    mutexLock.unlock();
  };
  _threads.clear();
};

auto CreateAsyncAwaitGroup() {
  std::unique_lock<std::mutex> mutexLock(vectorMutex);
  int startIndex = _threads.size();
  mutexLock.unlock();
  return [&startIndex]() {
    //    return;
    std::unique_lock<std::mutex> mutexLock(vectorMutex);
    int endIndex = _threads.size();

    //    int size = _threads.size();
    //    int size2 = startIndex;
    while (startIndex != endIndex && startIndex < _threads.size()) {

      printf("startIndexE: %zu, endIndex: %zu, size: %zu\n ", startIndex,
             endIndex, _threads.size());
      std::thread &threadProcess = _threads.at(startIndex);
      //
      if (threadProcess.joinable()) {
        _threads.erase(_threads.begin() + startIndex);

        mutexLock.unlock();
        threadProcess.join();
        mutexLock.lock();
      } else {
        _threads.erase(_threads.begin() + startIndex);
      };
      endIndex--;
    };
    mutexLock.unlock();
    printf("END SIZE: %zu\n ", _threads.size());
  };
}
