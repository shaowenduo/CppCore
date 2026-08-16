cmake_minimum_required(VERSION 3.16)
project(CppCore)                    
set(CMAKE_CXX_STANDARD 17)          
include_directories(include)        
add_executable(CppCore
    src/ThreadPool.cpp
    examples/main.cpp
)
add_executable(ThreadPoolTest
    src/ThreadPool.cpp
    tests/ThreadPool_test.cpp
)
add_executable(LRUTest
    tests/LRU_test.cpp
)