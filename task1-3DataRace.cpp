#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

int main() {
    int a{3}, counter{0};
    std::vector<std::thread> threads;
    std::mutex mtx;

    for (int i{0}; i < 3; ++i) {
        threads.emplace_back([&a, &counter, &mtx]() {
                std::lock_guard<std::mutex> lock(mtx);
                a *= a;
                std::cout << "Thread " << std::this_thread::get_id()<< " squared result is: " << a << std::endl;
                counter++;
                std::cout << "Thread " << std::this_thread::get_id()<< " incremented counter to: " << counter << std::endl;
        });
    }

    for (auto &thr : threads) {
        thr.join();
    }

    std::cout << "The final squared result is: " << a << std::endl;
    std::cout << "The final counter value is: " << counter << std::endl;

    return 0;
}