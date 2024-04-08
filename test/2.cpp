#include <iostream>
#include <string>
#define PI 3.14
using namespace std;

class circle
{
    // 访问权限 : 公共权限
public:
    // 属性:
    int m_r;
    //行为
    double calc(){
        return 2 * PI * m_r;
    }
};

class stude {

    public :
        string name;
        int number;
    void print(){
        cout << name <<" "<< number << endl;
        return;
    }
};

int main(){
    circle cl;
    cl.m_r = 10;
    cout << "圆的周长" << cl.calc() << endl;
    stude zhang3;
    zhang3.name = "zhangsha";
    zhang3.number = 1;
    zhang3.print();
    return 0;
    
}