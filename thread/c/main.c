#include "pool.h"
void taskFunc(void *arg)
{
    int num = *(int *)arg;
    printf("thread %ld is working, number = %d\n",
           pthread_self(), num);
    int ret = 3;
    ret *= num;
    printf("这里是%d\n", ret);
    sleep(1);
}

int main()
{
    // 创建线程池
    ThreadPool *pool = threadPoolCreate(5, 10, 50);
    printf("1\n");
    for (int i = 0; i < 100; ++i)
    {
        int *num = (int *)malloc(sizeof(int));
        *num = i + 2;
        printf("%d", *num);
        threadPoolAdd(pool, taskFunc, num);
    }
    // sleep(30);
    threadPoolDestroy(pool);
    return 0;
}