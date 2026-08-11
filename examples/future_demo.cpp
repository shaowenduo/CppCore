#include <iostream>
#include <future>
#include <thread>
template<typename F>
auto test(F&& func){
    using ReturnType=std::invoke_result_t<F>;
    std::packaged_task<ReturnType()> task(
        std::forward<F>(func)
    );
    auto future=task.get_future();
    std::thread(task);
    return future;
    warpper=[task=std::move(task)]{
        task();
    }
}







int main() {




}