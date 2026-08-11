#include <iostream>
#include <future>

int main() {
    std::packaged_task<int()> task([] {
        return 42;
    });

    std::future<int> future = task.get_future();

    task();

    std::cout << future.get() << std::endl;

    return 0;
}