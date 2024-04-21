#include <iostream>
#include <thread>
#include <chrono>
// 任务函数，将在新线程中执行
void taskFunction(int id) {
    std::cout << "Thread " << id << " is running\n";
    std::chrono::seconds waitTime(2);
    std::this_thread::sleep_for(waitTime);
    if(id==1){
    std::chrono::seconds waitTime(2);
    std::this_thread::sleep_for(waitTime); 
    }
    return;
}

int main() {
    // 创建两个线程并启动
    std::thread thread1(taskFunction, 1);
    std::thread thread2(taskFunction, 2);

    // 等待线程执行完成
    thread1.join();
    thread2.join();

    std::cout << "All threads have completed\n";

    return 0;
}
