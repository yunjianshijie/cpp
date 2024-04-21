#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
class ThreadPool
{
public:
    ThreadPool(size_t numThreads) : stop(false)
    {
        for (size_t i = 0; i < numThreads; ++i)
        {
            threads.emplace_back([this]
                                 {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mutex);
                        condition.wait(lock, [this] {
                            return stop || !tasks.empty();
                        });
                        if (stop && tasks.empty()) {
                            return;
                        }
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                } });
        }
    }

    template <class F>
    void enqueue(F &&f)
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            tasks.emplace(std::forward<F>(f));
        }
        condition.notify_one();
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &thread : threads)
        {
            thread.join();
        }
    }

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mutex;
    std::condition_variable condition;
    bool stop;
};

// 示例任务函数
void taskFunction(int id)
{
    std::cout << "Thread " << std::this_thread::get_id() << ": Task " << id << " is running\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << std::this_thread::get_id() << ": Task " << id << " is done\n";
}

int main()
{
    ThreadPool threadPool(4);

    // 将任务添加到线程池
    for (int i = 1; i <= 8; ++i)
    {
        threadPool.enqueue([i]
                           { taskFunction(i); });
    }

    // 等待所有任务完成
    std::this_thread::sleep_for(std::chrono::seconds(3));

    return 0;
}