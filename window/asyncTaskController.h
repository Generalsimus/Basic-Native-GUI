//
// Created by PC on 9/26/2023.
//

#ifndef CUDA_NEU_ASYNCTASKCONTROLLER_H
#define CUDA_NEU_ASYNCTASKCONTROLLER_H

#include <vector>
#include <future>

class AsyncTaskController {

private:
    std::vector<std::future<void>> tasks_;
    std::mutex mutex_;
public:

    template<typename Func, typename... Args>
    void addAsyncTask(Func &&func, Args &&... args);

    void awaitAll();

    void awaitStartEndAt(int start, int end);

    auto CreateAwaitGroup();
};


#endif //CUDA_NEU_ASYNCTASKCONTROLLER_H
