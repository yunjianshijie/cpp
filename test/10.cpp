
#include <iostream>
#include <string>
using namespace std;
class Person
{
public:
    mutable int m_age;
    int m_b;
    // this 是指针常量 指向不可以修改
    //
    void show_age() const
    {
        this->m_age = 100;
}
};
void test01(){
    Person p;
    p.m_age=10;
    p.show_age();
    cout << p.m_age;
}
void test02(){
    const Person p;
    // p.m_age = 0; //不能该
}

int main()
{


}
