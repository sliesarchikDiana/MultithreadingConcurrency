#include "task5.h"

void producer(SafeQueue& queue) {
    for (int i = 1; i <= 10; ++i) {
        queue.enqueue(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void consumer(SafeQueue& queue) {
    for (int i = 1; i <= 10; ++i) {
        queue.dequeue();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

int main() {
    SafeQueue queue;

    std::thread producer_thread(producer, std::ref(queue));
    std::thread consumer_thread(consumer, std::ref(queue));

    producer_thread.join();
    consumer_thread.join();

    return 0;
}