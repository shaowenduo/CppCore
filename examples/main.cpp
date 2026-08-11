#include "ThreadPool.h"
#include<iostream>

int main() {
    ThreadPool pool(4);

    auto f1 = pool.enqueue([] {
    return 42;
});

auto f2 = pool.enqueue([] {
    return 3.14;
});

auto f3 = pool.enqueue([] {
    return std::string("hello");
});
pool.enqueue([] {
    std::cout << "hello" << std::endl;
});
    std::cout << f1.get() << std::endl;
std::cout << f2.get() << std::endl;
std::cout << f3.get() << std::endl;

    return 0;
}