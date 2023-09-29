//
// Created by PC on 9/26/2023.
//

#include "asyncTaskController.h"


template<typename Func, typename... Args>
void AsyncTaskController::addAsyncTask(Func &&func, Args &&... args) {

    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.emplace_back(std::async(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...));

//    printf("ASYNC ADDED: %d \n", tasks_.size());
};


void AsyncTaskController::awaitAll() {
    size_t startAt = 0;
    while (true) {
        size_t tasksSize = this->tasks_.size();
        if (startAt < tasksSize) {
            const std::future<void> &task = this->tasks_[startAt];
            if (task.valid()) {
                task.wait();
            }
//            printf("ASYNC TASK END INX: %d\n", startAt);
            startAt++;
        } else {
            break;
        }
    }
    this->tasks_.clear();
}

void AsyncTaskController::awaitStartEndAt(int start, int end) {
//    printf("ASYNC AWAIT START AT: %d, END AT: %d\n", start, end);

    int startAt = start;
    while (startAt < end) {
//        printf("ASYNC WAIT: %d \n\n", startAt);
        const std::future<void> &task = this->tasks_[startAt];
        if (task.valid()) {
            task.wait();
        }
//        printf("ASYNC TASK END INX: %d\n", startAt);
        startAt++;
    };


    std::vector<std::future<void>>::iterator removeAt = (this->tasks_.end() - (end-start));

    // Erase the last 5 elements
    this->tasks_.erase(removeAt, this->tasks_.end());
}

auto AsyncTaskController::CreateAwaitGroup() {
    int startTasksCountAt = tasks_.size();
    auto self = this;

    return [startTasksCountAt, self]() {
        self->awaitStartEndAt(startTasksCountAt, self->tasks_.size());
    };
};
