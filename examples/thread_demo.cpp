#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <functional>
#include<future>
template<typename F>
void test(F&& func) {

    // 这里写：得到 func 的返回值类型
    // using ReturnType = ???
    using ReturnType=std::invoke_result_t<F>;
    // 暂时先不用执行 func
    std::packaged_task<ReturnType()> task(
        std::forward<F>(func)
    );
}

int main() {

    test([] {
        return 42;
    });

    test([] {
        return 3.14;
    });

    test([] {
        return std::string("hello");
    });
    test([]{
        std::cout<<"hello\n";
    });
    return 0;
}