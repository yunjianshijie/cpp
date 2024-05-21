#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#define pthread_num 10; //线程数
#define task_num 30;   //任务队列

using callback = void (*)(void *); //类型别名 callback，它被赋值为一个函数指针类型 void (*)(void *)。
struct Task
{
    Task()
    {
        function = nullptr;
        arg = nullptr;
    }
    Task(callback f, void *arg)
    {
        function = f;
        this->arg = arg;
    } // 析构
    void func{
        
    }
    callback function;
    
    void *arg;
};

class queue_tasks
{
public:
    std::queue<std::function<void()>> m_tast;

    void func(int t)
    {
        for (int i = 0; i < t; i++)
        {
        }
    }
    void addTask(Task &task)
    {
        if (m_queue.size() <= task_num)
        {
            m_queue.
        }
    }
    void addTask(callback func, void *arg);
    Task takeTask();

private:
    pthread_mutex_t m_mutex;  // 互斥锁
    std::queue<Task> m_queue; // 任务队列

}

class threadpool : public queue_tasks
{
    public:	
    threadpool()


	private:
	std::vector< std::thread > workers;// 工作线程组
	std::queue< std::function<void()> > tasks;// 任务队列
	// 异步
	std::mutex queue_mutex;	// 队列互斥锁
	std::condition_variable condition;	// 条件变量
	bool stop;	// 停止标志
}

main()
{
     
}

