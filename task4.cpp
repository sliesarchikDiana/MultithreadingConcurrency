#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;

void thread1_function() {
    std::cout << "Thread 1: Trying to lock mutex1..." << std::endl;
    mutex1.lock();
    std::cout << "Thread 1: Locked mutex1." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));


    std::cout << "Thread 1: Trying to lock mutex2..." << std::endl;
    mutex2.lock();
    std::cout << "Thread 1: Locked mutex2." << std::endl;
    std::cout << "Thread 1: Executing critical section..." << std::endl;

    mutex2.unlock();
    mutex1.unlock();
}

void thread2_function() {
    std::cout << "Thread 2: Trying to lock mutex2..." << std::endl;
    mutex2.lock();
    std::cout << "Thread 2: Locked mutex2." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "Thread 2: Trying to lock mutex1..." << std::endl;
    mutex1.lock();
    std::cout << "Thread 2: Locked mutex1." << std::endl;
    std::cout << "Thread 2: Executing critical section..." << std::endl;

    mutex1.unlock();
    mutex2.unlock();
}




void fixed_thread1_function() {
    std::scoped_lock lock(mutex1, mutex2);
    std::cout << "Thread 1: Executing critical section..." << std::endl;
}

void fixed_thread2_function() {
    std::scoped_lock lock(mutex1, mutex2);
    std::cout << "Thread 2: Executing critical section..." << std::endl;
}



int main() {
    std::thread t1(thread1_function);
    std::thread t2(thread2_function);

    t1.join();
    t2.join();

    std::cout << "Program completed successfully." << std::endl;
    return 0;
}