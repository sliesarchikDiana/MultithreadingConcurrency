#ifndef MULTITHREADINGCONCURRENCY_TASK5_H
#define MULTITHREADINGCONCURRENCY_TASK5_H
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class SafeQueue {
private:
    std::queue<int> queue;
    std::mutex mtx;
    std::condition_variable cv;
    const unsigned int max_size = 5;

public:
    void enqueue(int item) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return queue.size() < max_size; });

        queue.push(item);
        std::cout << "Produced: " << item << " (size: " << queue.size() << ")\n";

        cv.notify_one();
    }

    int dequeue() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return !queue.empty(); });

        int item = queue.front();
        queue.pop();
        std::cout << "Consumed: " << item << " (size: " << queue.size() << ")\n";

        cv.notify_one();
        return item;
    }
};


#endif //MULTITHREADINGCONCURRENCY_TASK5_H
