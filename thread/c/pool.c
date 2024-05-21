#include "pool.h"

// 创建线程池并初始化
ThreadPool *threadPoolCreate(int min, int max, int queueSize)
{
    ThreadPool *pool = (ThreadPool *)malloc(sizeof(ThreadPool));
    do
    { // 方便退出
        if (pool == NULL)
        {
            perror("threadpool malloc");
            break;
        }
        pool->threadIDs = (pthread_t *)malloc(sizeof(pthread_t) * max);
        if (!pool->threadIDs)
        {
            perror("threadpoolIDs malloc");
            break;
        }
        memset(pool->threadIDs, 0, sizeof(pthread_t) * max); // 初始化
        pool->minNum = min;
        pool->maxNum = max;
        pool->busyNum = 0;
        pool->liveNum = min; // 和最小个数相等
        pool->exitNum = 0;
        // 初始化锁
        if (pthread_mutex_init(&pool->mutexPool, NULL) != 0 ||
            pthread_mutex_init(&pool->mutexBusy, NULL) != 0 ||
            pthread_cond_init(&pool->notEmpty, NULL) != 0 ||
            pthread_cond_init(&pool->notFull, NULL) != 0)
        {
            printf("mutex or condition init fail...\n");
            break;
        }
        pool->taskQ = (Task *)malloc(sizeof(Task) * queueSize);
        pool->queueCapacity = queueSize;
        pool->queueSize = 0;
        pool->queueFront = 0;
        pool->queueRear = 0;

        pthread_create(&pool->managerID, NULL, manager, pool); // 管理者
        for (int i = 0; i < min; ++i)                          //
        {
            pthread_create(&pool->threadIDs[i], NULL, worker, pool); // 工作者
        }
        return pool;
    } while (1);
    if (pool->taskQ = NULL)
    {
        free(pool->taskQ);
    }
    if (pool->threadIDs == NULL)
    {
        free(pool->threadIDs);
    }
    if (pool == NULL)
    {
        free(pool);
    }
    return NULL;
}

int threadPoolDestroy(ThreadPool *pool) // 返回
{
    // 判断存在
    if (pool == NULL)
    {
        return -1;
    }
    // 等待线程完成

    // 销毁线程池
    pool->shutdown = 1;
    pthread_join(pool->managerID, NULL); // 等管理者结束
    if (pool->liveNum > 0)
    {
        for (int i = 0; i < pool->liveNum; i++)
        {
            pthread_cond_signal(&pool->notEmpty);
        }
    }

    // 销毁锁
    pthread_mutex_destroy(&pool->mutexPool);
    pthread_mutex_destroy(&pool->mutexBusy);
    pthread_cond_destroy(&pool->notEmpty);
    pthread_cond_destroy(&pool->notFull);

    // 释放内存
    if (pool->taskQ = NULL)
    {
        free(pool->taskQ);
    }
    if (pool->threadIDs == NULL)
    {
        free(pool->threadIDs);
    }
    if (pool == NULL)
    {
        free(pool);
        pool = NULL;
    }
    return 0;
}

void threadPoolAdd(ThreadPool *pool, void (*func)(void *), void *arg)
{
    // void(*func)(void*), void* arg 任务
    pthread_mutex_lock(&(pool->mutexPool));
    printf("添加");
    if (pool->shutdown == 0 && pool->queueSize == pool->queueCapacity)
    {
        // 排不下了
        printf("在排队了");
        pthread_cond_wait(&pool->notFull, &pool->mutexPool);
        // 就堵塞线程
    }
    if (pool->shutdown == 1)
    {
        pthread_mutex_unlock(&pool->mutexPool);
        return;
    }
    // 排到任务队列里面
    pool->taskQ[pool->queueRear].function = func;
    pool->taskQ[pool->queueRear].arg = arg;
    pool->queueRear = (pool->queueRear + 1) % pool->queueCapacity;
    pool->queueSize++;
    pthread_mutex_unlock(&pool->mutexPool);
}

int threadPoolBusyNum(ThreadPool *pool)
{
    if (pool == NULL)
    {
        return 0;
    }
    //
    pthread_mutex_lock(&pool->mutexBusy);
    int ret = pool->busyNum;
    pthread_mutex_unlock(&pool->mutexBusy);
    return ret;
}

int threadPoolAliveNum(ThreadPool *pool)
{
    if (pool == NULL)
    {
        return 0;
    }
    //
    pthread_mutex_lock(&pool->mutexPool);
    int ret = pool->liveNum;
    pthread_mutex_unlock(&pool->mutexPool);
    return ret;
}

void *worker(void *arg)
{
    ThreadPool *pool = (ThreadPool *)arg;
    while (1)
    { // 不断循环看 查看是否能工作
        pthread_mutex_lock(&pool->mutexPool); //所住线程池
        while (pool->queueSize == 0 && pool->shutdown==0){
            pthread_cond_wait(&pool->notEmpty,&pool->mutexPool);
            //堵塞
            if(pool->exitNum>0){
                pool->exitNum--;
                if(pool->liveNum > pool->minNum){
                    pool->liveNum-- ;
                    pthread_mutex_unlock(&pool->mutexPool);
                    threadExit(pool);
                }
            }
        } 
        if(pool->shutdown==1){
            pthread_mutex_unlock(&pool->mutexPool);
            threadPoolDestroy(pool);
            return NULL;
        }
        //等待成功收到命令
        //获取任务
        Task task_new=pool->taskQ[pool->queueFront];
        task_new.function = pool->taskQ[pool->queueFront].function;
        pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;//循环使用
        pool->queueSize--;

        pthread_cond_signal(&pool->notFull);
        pthread_mutex_unlock(&pool->mutexPool);
        //给解锁 
        printf("thread %ld start working...\n", pthread_self());
        pthread_mutex_lock(&pool->mutexBusy);//增加工作线程
        pool->busyNum++;
        pthread_mutex_unlock(&pool->mutexBusy);
        task_new.function(task_new.arg);//完成任务
        free(task_new.arg);
        task_new.arg = NULL;
        //释放掉
        printf("thread %ld end working...\n", pthread_self());
        pthread_mutex_lock(&pool->mutexBusy); // 完成后，减少工作线程
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexBusy);
    }
    return NULL; 
}

void *manager(void *arg){
    int NUMBER = 10;
    ThreadPool *pool = (ThreadPool *)arg;
    while (!pool->shutdown)
    {
        sleep(3); // 每3秒查一次
        // 取出线程池中任务的数量和当前线程的数量

        pthread_mutex_lock(&pool->mutexPool);
        int queueSize = pool->queueSize;
        int liveNum = pool->liveNum;
        pthread_mutex_unlock(&pool->mutexPool);

        // 取出忙的线程的数量
        pthread_mutex_lock(&pool->mutexBusy);
        int busyNum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);

        // 添加线程
        // 任务的个数>存活的线程个数 && 存活的线程数<最大线程数
        if (queueSize > liveNum && liveNum < pool->maxNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            int counter = 0;
            for (int i = 0; i < pool->maxNum && counter < NUMBER
                && pool->liveNum < pool->maxNum; ++i)
            {
                if (pool->threadIDs[i] == 0)
                {
                    pthread_create(&pool->threadIDs[i], NULL, worker, pool);
                    counter++;
                    pool->liveNum++;
                }
            }
            pthread_mutex_unlock(&pool->mutexPool);
        }
        // 销毁线程
        // 忙的线程*2 < 存活的线程数 && 存活的线程>最小线程数
        if (busyNum * 2 < liveNum && liveNum > pool->minNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            pool->exitNum = NUMBER;
            pthread_mutex_unlock(&pool->mutexPool);
            // 让工作的线程自杀
            for (int i = 0; i < NUMBER; ++i)
            {
                pthread_cond_signal(&pool->notEmpty);
            }
        }
    }
    return NULL;
    }
    


void threadExit(ThreadPool* pool)
{
    pthread_t tid = pthread_self();
    for (int i = 0; i < pool->maxNum; ++i)
    {
        if (pool->threadIDs[i] == tid)
        {
            pool->threadIDs[i] = 0;
            printf("threadExit() called, %ld exiting...\n", tid);
            break;
        }
    }
    pthread_exit(NULL);
}