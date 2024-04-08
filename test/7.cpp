#include <iostream>
#include <string>
using namespace std;
class Phone
{
public:
    string p_Name;
    Phone(string p_name)
    {
        p_Name = p_name;
        cout << "xx" << endl;
    }
};
class Person
{
public:
    string m_name;
    Phone m_phone;
    Person(string name, string phone) : m_name(name), m_phone(phone)
    {
        cout << "w" << endl;
    }
};
int main()
{
    Person p("张三", "huawei");

}