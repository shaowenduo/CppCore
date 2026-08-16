#include "LRUCache.h"
#include<iostream>
#include<string>
#include<optional>
int main(){
    LRUCache<int,std::string> LC(20);
    // 1. 插入后 size 是否正确

    bool size_1=(LC.size()==0);
    for(int i=1;i<=5;i++){
        LC.put(i,"test_size");
    }

    bool size_2=(LC.size()==5);
    for(int i=6;i<=30;i++){
        LC.put(i,"test_size");
    }

    bool size_3=(LC.size()==20);
    if(size_1&&size_2&&size_3){
        std::cout<<"test1 pass"<<std::endl;
    }else std::cout<<"test1 fail"<<std::endl;
    
    // 2. 超容量后最旧元素是否被淘汰
    if(!LC.get(5).has_value()){
        std::cout<<"test2 pass"<<std::endl;
    }else std::cout<<"test2 fail"<<std::endl;
    // 3. get 是否会把元素移到 front
    LC.get(11);
    LC.put(31,"test_size");
    if(LC.get(11).has_value()&&!LC.get(12).has_value()){
        std::cout<<"test3 pass"<<std::endl;
    }else std::cout<<"test3 fail"<<std::endl;

    // 4. put 已存在 key 是否更新 value
    LC.put(13,"put_renew_test");
    if(LC.get(13).has_value()){
        if(LC.get(13).value()=="put_renew_test"){
            std::cout<<"test4 pass"<<std::endl;
        }else std::cout<<"test4 fail"<<std::endl;
    }else std::cout<<"test4 fail"<<std::endl;
    // 5. put 已存在 key 是否更新 LRU 顺序
    LC.put(32,"test_put");
    if(LC.get(13).has_value()){
        std::cout<<"test5 pass"<<std::endl;
    }else std::cout<<"test5 fail"<<std::endl;
    // 6. 不存在 key 是否返回 nullopt
    if(LC.get(100)==std::nullopt){
        std::cout<<"test6 pass"<<std::endl;
    }else std::cout<<"test6 fail"<<std::endl;
    // 7. capacity = 0
    LRUCache<int,std::string> LC_2(0);
    for(int i=1;i<=5;i++){
        LC_2.put(i,"test_size");
    }
    if(!LC_2.get(5).has_value()&&LC_2.size()==0){
        std::cout<<"test7 pass"<<std::endl;
    }else std::cout<<"test7 fail"<<std::endl;
    LRUCache<int, std::string> a(3);

    a.put(1, "A");
    a.put(2, "B");
    a.put(3, "C");

    LRUCache<int, std::string> b = std::move(a);

    auto result = b.get(2);

    if (result && *result == "B") {
        std::cout << "move constructor pass\n";
    } else {
        std::cout << "move constructor fail\n";
    }
    LRUCache<int, std::string> c(10);

    c.put(100, "old");

    c = std::move(b);

    auto result2 = c.get(2);

    if (result2 && *result2 == "B") {
        std::cout << "move assignment pass\n";
    } else {
        std::cout << "move assignment fail\n";
    }
    return 0;
}
