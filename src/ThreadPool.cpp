#include "ThreadPool.h"
#include "Logger.h"
#include<chrono>
#include<iostream>
ThreadPool::ThreadPool(size_t threadCount):stop(false)
{
    workers.reserve(threadCount);
    Logger::info("ThreadPool started");
    for(size_t i=0;i<threadCount;i++){
        workers.emplace_back([this] {
        Logger::info("worker started");
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
            Logger::info("task start");
            task();
            Logger::info("task finished");
        }
        });
    }
    
}

ThreadPool::~ThreadPool(){
    Logger::info("ThreadPool started");
    {
        std::lock_guard<std::mutex> lock(mx);
        stop=true;
    }
    Logger::info("ThreadPool stopped");
    cv.notify_all();
    for(auto& worker:workers){
        worker.join();
    }

}

