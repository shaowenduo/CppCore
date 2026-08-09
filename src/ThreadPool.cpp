#include "ThreadPool.h"
#include<chrono>
#include<iostream>
ThreadPool::ThreadPool(size_t threadCount):stop(false)
{
    workers.reserve(threadCount);
    for(size_t i=0;i<threadCount;i++){
        workers.emplace_back([this] {

        while (true) {

            std::unique_lock<std::mutex> lock(mx);

            cv.wait(lock, [this] {
                
                return !tasks.empty()||stop;
            });

            // 如果需要停止
            
                
            if (stop&&tasks.empty()) {
                return;
            }
            
            

            // 取出任务
            auto task = std::move(tasks.front());

            // 删除任务
            tasks.pop();

            // 解锁
            lock.unlock();
            // 执行任务
            task();
        }
        });
    }
    
}

ThreadPool::~ThreadPool(){
    {
        std::lock_guard<std::mutex> lock(mx);
        stop=true;
    }
    
    cv.notify_all();
    for(auto& worker:workers){
        worker.join();
    }

}

void ThreadPool::enqueue(std::function<void()> task){
    {
        std::lock_guard<std::mutex> lock(mx);
        tasks.emplace(std::move(task));
    }
    
    cv.notify_one();
}