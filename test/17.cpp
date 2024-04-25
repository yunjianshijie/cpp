#include <iostream>
#include <thread>
#include <vector>
#include <algorithm> //标准算法头文件
using namespace std;

template <typename T>
void myswap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}
void myPrint(int val)
{
    cout << val << endl;
}
void test01()
{
    int a = 0;
    int b = 1;
    char c = 'c';
    myswap(a, b);
    //
    // myswap(a, c);//错误

    cout << "a =" << a << " b= " << b << endl;
    myswap<int>(a, b);
    cout << "a =" << a << " b= " << b << endl;
}
void test02()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    auto itBegin = v.begin();
    vector<int>::iterator itEnd = v.end(); // 结束迭代器
    while (itBegin != itEnd)
    {
        cout << *itBegin << endl;
        itBegin++;
    }
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    { cout << *it << endl;
    }
    for_each(v.begin(), v.end(), myPrint); // 将前两个遍历，接出数据循环，调用函数接口
}
//三种循环
void print_vector(vector<int> v){
    for (auto it = v.begin(); it != v.end();it++){
        cout << *it << endl;
    }
}
void test03(){
    vector<int> v1(2,6);
    

}

int main()
{
    test02();
    
}