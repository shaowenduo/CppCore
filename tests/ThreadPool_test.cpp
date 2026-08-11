#include "ThreadPool.h"

#include <atomic>
#include <cassert>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>


void test_void_task() {
    ThreadPool pool(4);

    bool done = false;

    auto future = pool.enqueue([&done] {
        done = true;
    });

    future.get();

    assert(done);

    std::cout << "Test 1 passed: void task\n";
}


void test_return_value() {
    ThreadPool pool(4);

    auto future = pool.enqueue([] {
        return 42;
    });

    assert(future.get() == 42);

    std::cout << "Test 2 passed: return value\n";
}


void test_multiple_tasks() {
    ThreadPool pool(4);

    auto f1 = pool.enqueue([] { return 10; });
    auto f2 = pool.enqueue([] { return 20; });
    auto f3 = pool.enqueue([] { return 30; });
    auto f4 = pool.enqueue([] { return 40; });

    assert(f1.get() == 10);
    assert(f2.get() == 20);
    assert(f3.get() == 30);
    assert(f4.get() == 40);

    std::cout << "Test 3 passed: multiple tasks\n";
}


void test_parallel_execution() {
    ThreadPool pool(4);

    auto start = std::chrono::steady_clock::now();

    auto f1 = pool.enqueue([] {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 1;
    });

    auto f2 = pool.enqueue([] {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 2;
    });

    auto f3 = pool.enqueue([] {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 3;
    });

    auto f4 = pool.enqueue([] {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 4;
    });

    assert(f1.get() == 1);
    assert(f2.get() == 2);
    assert(f3.get() == 3);
    assert(f4.get() == 4);

    auto end = std::chrono::steady_clock::now();

    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start
        ).count();

    std::cout << "Elapsed: " << elapsed << " ms\n";

    assert(elapsed < 2000);

    std::cout << "Test 4 passed: parallel execution\n";
}


void test_shutdown_with_pending_tasks() {
    bool finished = false;

    {
        ThreadPool pool(4);

        pool.enqueue([&finished] {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            finished = true;
        });
    }

    assert(finished);

    std::cout << "Test 5 passed: shutdown with pending tasks\n";
}


void test_exception() {
    ThreadPool pool(4);

    auto future = pool.enqueue([]() -> int {
        throw std::runtime_error("task failed");
    });

    bool caught = false;

    try {
        future.get();
    }
    catch (const std::runtime_error& e) {
        caught = true;
        std::cout << "Caught: " << e.what() << '\n';
    }

    assert(caught);

    std::cout << "Test 6 passed: exception propagation\n";
}


void test_many_tasks() {
    ThreadPool pool(4);

    std::atomic<int> counter{0};

    const int taskCount = 1000;

    std::vector<std::future<void>> futures;

    for (int i = 0; i < taskCount; ++i) {
        futures.push_back(
            pool.enqueue([&counter] {
                counter.fetch_add(1);
            })
        );
    }

    for (auto& future : futures) {
        future.get();
    }

    assert(counter == taskCount);

    std::cout << "Test 7 passed: many tasks\n";
}


int main() {
    test_void_task();
    test_return_value();
    test_multiple_tasks();
    test_parallel_execution();
    test_shutdown_with_pending_tasks();
    test_exception();
    test_many_tasks();

    std::cout << "\nAll tests passed!\n";

    return 0;
}