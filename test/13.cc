
#include <iostream>
#include <string>
using namespace std;
class A{
    public:
        int m_a;
        int m_b;
    A(){
        cout << "AAAAA";
    }
    protected:
        int m_d;
    private:
        int m_f;//父类属性能继承，但是编译器给隐藏了 -
    
};
class B:public A
{
    public:
    B(){
        cout << "BBB\n";
    };
    int m_c;
};
int main(){
    A s;
    s.m_a = 1;
    s.m_b = 2;
    B s1;
    s1.m_c =1;
}