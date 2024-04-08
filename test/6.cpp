#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    int age;
    int *M_hight;
    Person()
    {
        cout << "无参构造函数" << endl; // 如果不写这个函数，系统空实现（什么都没有）
    }
    Person(int a, int hight)
    {
        cout << "有参构造函数" << endl;
        M_hight = new int(hight); // 在堆区开辟一个数据
        age = a;
    }
    Person(const Person &p){
        cout << "拷贝函数" << endl;
        age = p.age;
        M_hight = new int(*p.M_hight); //需要这样深拷贝
    }
    ~Person() // 将堆区开辟的数据做释放操作
    {
        if (M_hight != NULL)
        {
            delete M_hight;
            M_hight = NULL;
        }
        cout << "Person的析构函数" << endl;
    }
};

void test01()
{
    Person p1(19, 160);
    cout << "p1 " << p1.age << "  " << *p1.M_hight << endl;
    Person p2(p1);
    cout << "p2 " << p2.age << "  " << *p2.M_hight << endl; //浅拷贝，会造成堆区重复释放
}

int main()
{
    test01();
}
//这个程序会释放两次 