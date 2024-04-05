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

void test01(){
    Person p1(20);
    Person p2(p1);
}
int main()
{
    test01();
}