#include <iostream>
#include <string>
using namespace std;
class Person
{
public:
    static int a;
    static void func(){
        cout << "xxx" << endl;
    }//

private:
    static int b;//权限


};
int Person::a = 100; // 在定义和初始化之外 ，后面定义了所以编译 错误

void test01()
{
    Person p;

    cout << Person::a << endl;
}
int main()
{
    test01();
    Person::func();//通过类名访问他
    Person p2;
    p2.a = 200;
    cout << Person::a << endl;
    cout << p2.a << endl;
}
