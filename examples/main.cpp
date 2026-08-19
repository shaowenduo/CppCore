#include "ThreadPool.h"
#include "LRUCache.h"
#include "Logger.h"

#include <iostream>
#include <string>

int main() {
    Logger::setLevel(LogLevel::Info);

    Logger::info("CppCore demo started");

    LRUCache<int, std::string> cache(3);

    cache.put(1, "Player");
    cache.put(2, "Enemy");
    cache.put(3, "Map");

    auto value = cache.get(2);

    if (value) {
        Logger::info("LRU get: " + *value);
    } else {
        Logger::warning("LRU key not found");
    }

    ThreadPool pool(4);

    auto f1 = pool.enqueue([] {
        return 42;
    });

    auto f2 = pool.enqueue([] {
        return std::string("hello");
    });

    Logger::info("Tasks submitted");

    Logger::info("f1 result = " + std::to_string(f1.get()));
    Logger::info("f2 result = " + f2.get());

    Logger::info("CppCore demo finished");

    return 0;
}