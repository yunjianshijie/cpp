#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    int age;
    // string name;
    Person()
    {
        cout << "无参构造函数" << endl; // 如果不写这个函数，系统空实现（什么都没有）
    }
    Person(int a)
    {
        cout << "有参构造" << endl;
        age = a;
    }
    Person(const Person &p)
    { // 以引用的方式传入
        age = p.age;
        cout << "拷贝构造" << endl;
    }
    ~Person()
    {
        cout << "析构函数" << endl;
    }
};
void test01()
{             // 1括号法
    Person p; // 在栈上的数据，所以销毁对象

    // 不要写 Person p(); -> 编译器会认为函数的声明
    Person p2(10);
    Person p3(p2);
    cout << p2.age << "  " << p3.age << endl;
}
void test02()
{
    // 显示法
    Person p1;
    Person p2 = Person(10); // 调用有参 ->匿名对象
    Person p3 = Person(p2); // 拷贝
    cout << p2.age << "  " << p3.age << endl;
}
void test03() {
    //隐式转换
    Person p1 = 10;
    Person p2 = p1;
     cout << p1.age << "  " << p2.age << endl;
}
int main()
{

    // test01();
    // test02();
    test03();
}