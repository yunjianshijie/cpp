#include <iostream>
#include <string>
using namespace std;
class Person
{
private:
    /* data */
public:
    int age;
    Person(/* args */)
    {
        cout << "Person 默认构造函数调用" << endl;
    }
    Person(const Person &a)
    {
        cout << "拷贝构造函数" << endl;
        age = a.age;
    }
    Person(int a)
    {
        cout << "有参构造函数" << endl;
        age = a;
    }

    ~Person()
    {
        cout << "Person的析构函数" << endl;
    }
};

void test01()
{
    Person p1(20);
    Person p2(p1);
}
void dowork(Person p)
{
}
void test02()
{
    Person p;
    dowork(p); // 实参传给形参时，会变成拷贝
}
Person test03()
{
    Person p;
    p.age = 10;
    cout << p.age << endl;
    return p;
}
int main()
{
    // test03();
    Person p1 = test03(); // 这里会发生拷贝 ? 在这里只发生默认构造
    //这里没有发生构造?
    cout << p1.age << endl;
}