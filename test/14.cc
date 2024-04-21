#include <iostream>
#include <string>
using namespace std;

class dong{
    public:
    //虚函数
   virtual void speak(){
        cout << "dong" << endl;
    }
};

class Cat :public dong
 {
    public:
    void speak(){
        cout << "cat" << endl;
    }
};

void dospeak(dong & animal){
    animal.speak(); // 动态多态： 有继承，子类要重写父类中的虚函数
    //父类的引用（指针）指向子类对象
}
void task01(){
    Cat cat;
    dospeak(cat);
}
int main(){
    task01();
}