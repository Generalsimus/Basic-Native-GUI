//
// Created by PC on 9/9/2023.
//

#ifndef CUDA_NEU_EVENT_H
#define CUDA_NEU_EVENT_H

#include <functional>
#include <vector>
#include <future>


using TouchEventType = std::function<void(int, int)>;

class AsyncManager {
public:
    // Add an asynchronous task to the group
    template<typename Func, typename... Args>
    void AddTask(Func&& func, Args&&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        tasks_.emplace_back(std::async(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...));
    }

    // Await all tasks in the group
    void AwaitAll() {
        for (auto& task : tasks_) {
            task.wait();
        }
    }

private:
    std::vector<std::future<void>> tasks_;
    std::mutex mutex_;
};

class Event {

private:
    TouchEventType *TouchEventChain = nullptr;


    std::vector<std::future<void>> tasks_;
    std::mutex mutex_;


public:

    template<typename Func, typename... Args>
    void addAsyncTask(Func&& func, Args&&... args);

    void awaitAll();


    void addTouchEvent(TouchEventType callBack);

    void dispatchTouchEvent(int x, int y);


protected:
    Event();

};


#endif //CUDA_NEU_EVENT_H
