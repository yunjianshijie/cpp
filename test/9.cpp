#include <iostream>
#include <string>
using namespace std;
class Person
{
public:
    int age;
    Person(int age)
    {
        // this->age = age;//this指针指向
        Person ::age = age;
    }
    Person Person_add(Person &p)
    {
        this->age += p.age;
        return *this;
    }
    void show_name()
    {
        cout << "z" << endl;
    }
    void show_age()
    {
        if(this==NULL){
            return;
        }
        cout << "age= " << age << endl;
    }
};

void test01()
{
    Person p(10);
    Person p2(10);
    cout << p.Person_add(p2).Person_add(p2).Person_add(p2).age << "\n"; // 这里是40
    cout << p.age << endl;                                              // 值还是20
}
void test02()
{
    Person *p = NULL;
    p->show_name();
    p->show_age();
}
int main()
{
    test01();
    test02();
}
