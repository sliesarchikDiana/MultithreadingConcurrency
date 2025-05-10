#include <iostream>
#include <thread>
#include <vector>
int main(){
    int a{3};
    std::vector<std::thread> threads;
    std::mutex mtx;
    for (int i{0}; i < 3; ++i) {
        threads.emplace_back([&a, &mtx](){std::lock_guard<std::mutex> lock(mtx) ;a*=a;});
        std::cout<<"Result of exponent from thread"<<threads[i].get_id()<<": "<<a<<std::endl;
    }
    for (auto &thr : threads) {
        thr.join();
    }
    std::cout<<"The final result is: "<<a;




    return 0;
}