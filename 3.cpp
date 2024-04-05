#include <iostream>
#include <string>
using namespace std;

class person
{
    private :
    string m_name;
    int age =18;//默认值
    string love;

    public:
    void set_name(string name){
        m_name = name;
    }
    string get_name(){
        return m_name;
    }
};


int main()
{
    person p;
    p.set_name("张三");
    // p.m_name = "张三"; //不能这样写权限不足
    cout << p.get_name() << endl;
}