#pragma once
#include<vector>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<functional>
#include<future>
class ThreadPool{
public:
    ThreadPool(size_t threadCount);
    ~ThreadPool();
    template<typename F>
    auto enqueue(F&& func){
        using ReturnType=std::invoke_result_t<F>;
        auto task=std::make_shared<
        std::packaged_task<ReturnType()>
        >(
            std::forward<F>(func)
        );
        auto future=task->get_future();
        auto wrapper=[task]()mutable{
            (*task)();
        };
        {
            std::lock_guard<std::mutex> lock(mx);
            tasks.emplace(std::move(wrapper));
        }
        cv.notify_one();
        return future;

    }
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex mx;
    std::condition_variable cv;
    bool stop;

};