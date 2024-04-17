
#include <iostream>
#include <string>
using namespace std;
class Person
{
    friend ostream &operator<<(ostream &out, Person &p);

public:
    int m_b;
    int m_a;
    Person operator+(int n)
    {
        Person teep;
        teep.m_a = this->m_a + n;
        teep.m_b = this->m_b + n;

        return teep;
    } // 通过成员函数重载 +
    // 运算符重载也能重载函数重载
   DA E Q w r Y H N J C
    {
        this->m_b++;
        this->m_a++;
        return *this;
    } // 前置++
    Person operator++(int)
    { // 返回值是不可以当作函数重载 ,所以int 为占位参数
        // 先理录当时结果
        Person tmep = *this;
        // 后 递増
        this->m_b++;
        this->m_a++;
        return tmep;
    }
};
Person operator+(Person &p1, Person &p2)
{
    Person teep;
    teep.m_a = p1.m_a + p2.m_a;
    teep.m_b = p1.m_b + p2.m_b;
    return teep;
}
ostream &operator<<(ostream &out, Person &p)
{
    out << "m_a=" << p.m_a << " m_b=" << p.m_b << endl;
    return out;
}

void test01()
{
    Person p1;
    p1.m_a = 10;
    p1.m_b = 10;
    Person p2;
    p2.m_a = 12;
    p2.m_b = 122;
    Person p3 = p1 + 10;
    cout << p3.m_a << "  " << p3.m_b << "\n";
    p3++;
    cout << p3;
    cout << p3;
}
void test02()
{
    Person p;
    // p.m_age = 0; //不能该
}

int main()
{
    test01();
}
