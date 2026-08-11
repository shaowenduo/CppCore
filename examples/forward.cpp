#include<iostream>
#include<utility>
#include<future>
void foo(int& x){
    std::cout<<"left"<<std::endl;
}

void foo(int&& x){
    std::cout<<"right"<<std::endl;
}


template<typename F>
void test(F&& func) {

    using ReturnType = std::invoke_result_t<F>;

    std::packaged_task<ReturnType()> task(
        std::forward<F>(func)
    );

    auto future = task.get_future();

    task();

    std::cout << future.get() << std::endl;
    // 这里怎么办？
}
int main() {

    test([] {
        return 42;
    });

    return 0;
}

















