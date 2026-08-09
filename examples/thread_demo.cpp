#include <iostream>
#include <thread>
#include<vector>
int main() {
    
    std::thread t(
        []{
            std::cout<<"hello"<<std::endl;
        }
    );
    std::cout<<"hello"<<std::endl;
    t.join();
    return 0;
}
int main() {
    std::vector<std::thread> workers;
    for(int i=0;i<4;i++){
        workers.emplace_back([]{
            std::cout<<"hello"<<std::endl;
        });
    }
    return 0;
}