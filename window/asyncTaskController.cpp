//
// Created by PC on 9/26/2023.
//

#include "asyncTaskController.h"




template<typename Func, typename... Args>
void AsyncTaskController::addAsyncTask(Func &&func, Args &&... args) {

    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.emplace_back(std::async(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...));

}


void AsyncTaskController::awaitAll() {
    size_t startAt = 0;
    while (true) {
        size_t tasksSize = tasks_.size();
        if (startAt < tasksSize) {
            auto task = tasks_[startAt];
            if (task.valid()) {
                task.wait();
            }
        }else{
            break;
        }
    }
    tasks_.clear();
}

AsyncTaskController* AsyncTaskController::CreateAsyncGroup() {
    return new AsyncTaskController();
}
