#include "ThreadPool.h"
#include<iostream>
int main(){
    ThreadPool pool(4);
    pool.enqueue([] {
        std::cout << "task 1 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "task 1 end" << std::endl;
    });

    pool.enqueue([] {
        std::cout << "task 2 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "task 2 end" << std::endl;
    });

    pool.enqueue([] {
        std::cout << "task 3 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "task 3 end" << std::endl;
    });

    pool.enqueue([] {
        std::cout << "task 4 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "task 4 end" << std::endl;
    });
    pool.enqueue([] {
        std::cout << "task 5 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "task 5 end" << std::endl;
    });
    pool.enqueue([] {
        std::cout << "task 6 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "task 6 end" << std::endl;
    });
    return 0;
}