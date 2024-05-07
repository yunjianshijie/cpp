#include <iostream>
#include <string>
#include <thread>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;
const int thread_num = 10;
vector<int> data() // 随机
{
    random_device rd;
    mt19937 engine(rd());
    int datasetSize = 100000;
    int minNum = 1;
    int maxNum = 10000;
    uniform_int_distribution<int> dist(minNum, maxNum);
    vector<int> dataset(datasetSize);
    for (int i = 0; i < datasetSize; i++)
    {
        dataset[i] = dist(engine);
    }
    return dataset;
}
void print(vector<int> data_t)
{ // 输出
    for (int i = 0; i < data_t.size() / 100; i++)
    {
        cout << data_t[i * 100];
    }
}

void sortSubarray(vector<int> &arr, int left, int right)
{
    sort(arr.begin() + left, arr.begin() + right + 1);
}

void mergeSort(vector<int> &arr, int left, int right, int mid)
{
    vector<int> temp(right - left + 1);
    int i = left; //  左
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }
        k++;
    } // 一个一个输
    while (i <= mid)
    {
        temp[k] = arr[i];
        i++;
    }
    while (j <= mid)
    {
        temp[k] == arr[j];
        j++;
    } // 处理后事
}

void pthread_sort(vector<int> &arr)
{ // 并发
    int n = arr.size();
    int blockSize = n / thread_num;
    vector<thread> threads;
    for (int i = 0; i < thread_num; i++)
    {
        int left = i * blockSize;
        int right = left + blockSize - 1;
        threads.emplace_back(sortSubarray, std::ref(arr), left, right);
    }
    for (auto &t : threads)
    {
        t.join();
    } // 等到完成
    int thread_num_h = thread_num;
    while (thread_num_h > 1)
    {
        int newthread_num = (thread_num_h + 1) / 2;
        vector<thread> merge_threads;
        for (int i = 0; i < newthread_num; i++)
        {
            int left = i * blockSize * 2;
            int mid = (i * blockSize * 2) + (blockSize - 1);
            int right = std::min((i * blockSize * 2) + (2 * blockSize - 1), n - 1);
            merge_threads.emplace_back(mergeSort, std::ref(arr), left, mid, right);
        }
        for (auto &t : merge_threads)
        {
            t.join();
        } // 等待

        thread_num_h = newthread_num;
        blockSize *= 2;
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    vector<int> data_t = data();
    cout << data_t.size() << endl;
    // 随机数组
    pthread_sort(data_t);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  //  print(data_t);
    std::cout << "执行时间: " << duration.count() << " 毫秒" << std::endl;
    return 0;
}