---
title: cpp笔记
abbrlink: 11
index_img: /img/elysia2.jpg
banner_img: /img/elysia2.jpg
date: 2024-04-01
tags: cpp
---
## 重载
C++ 中的函数重载可以发生在全局作用域、类的成员函数以及命名空间中。函数重载的条件是函数名称相同，但参数列表必须不同。参数列表的不同可以通过参数的类型、顺序和个数来实现。返回值类型不同不足以实现函数重载，因为函数重载的决策是在编译时进行的。

~~~cpp
#include <iostream>

void display(int num) {
    std::cout << "Integer: " << num << std::endl;
}

void display(double num) {
    std::cout << "Double: " << num << std::endl;
}

int main() {
    display(10);
    display(3.14);
    return 0;
}

~~~

还有一个运算符重载

~~~cpp
#include <iostream>

class Vector2D {
public:
    double x, y;

    Vector2D(double x, double y) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& other) {
        return Vector2D(x + other.x, y + other.y);
    }
};

int main() {
    Vector2D v1(1.0, 2.0);
    Vector2D v2(3.0, 4.0);
    Vector2D result = v1 + v2;

    std::cout << "Result: (" << result.x << ", " << result.y << ")" << std::endl;

    return 0;
}
~~~

> 这个没看懂

## std::string 类

### 储和访问字符串内容
储和访问字符串内容：std::string 对象可以存储任意长度的字符串。
您可以使用赋值运算符 = 或构造函数将字符串赋值给 std::string 对象，
并使用 [] 运算符 或 成员函数 at() 来访问字符串中的单个字符。
~~~cpp
std::string str = "Hello";
char ch = str[0];  // 访问第一个字符 'H'
char ch2 = str.at(1);  // 访问第二个字符 'e'
 //str.at(1) -> 成员函数
~~~
### 获取字符串长度：
使用 length() 或 size() 成员函数可以获取字符串的长度（字符数）。
~~~cpp
std::string str = "Hello";
int len = str.length();
~~~

### 字符串拼接
使用 + 运算符或 append() 成员函数可以将字符串拼接起来。
~~~cpp
std::string str1 = "Hello";
std::string str2 = "World";
std::string result = str1 + " " + str2;  // 拼接字符串 "Hello World"
//还有两种
std::string str3 = "Hello";
str3.append(" World");  // 拼接字符串 "Hello World"
~~~

### 字符串提取

子字符串提取：使用 substr() 成员函数可以从一个字符串中提取出指定位置和长度的子字符串。

~~~cpp
std::string str1 ="hello, World!"
std::string substr = str.substr(7.5);// 提取从索引位置 7 开始的长度为 5 的子字符串，结果为 "World"

~~~

### 字符串比较
使用 ==、!=、<、> 等运算符可以进行字符串的比较操作。
~~~cpp
std::string str1 = "Hello";
std::string str2 = "World";
bool equal = (str1 == str2);  // 判断两个字符串是否相等
bool less = (str1 < str2);  // 判断 str1 是否小于 str2
~~~


## 类和对象
 > 3大特性 **封装** **继承** **多态**

### 封装

>语法: class 类名{ 访问权限: 属性/行为};

一个简单的类的案例：
~~~ cpp
#include <iostream>
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

int main(){
    circle cl;//通过一个类创建一个过程 —> 实例化
    cl.m_r = 10;
    cout << "圆的周长" << cl.calc() << endl;
    return 0;
}
~~~


>类中的属性与行为 统称为*成员*

> 属性 -> 成员属性，变量   
> 行为-> 成员函数

 访问权限 

 1. public : 公共权限  // 成员在类内能访问 类外能访问
 2. protected : 保护权限 // 成员 类内能访问 类外不能访问 -> 儿子可以访问父类的内容
 3. private : 私有权限 //成员 类内能访问 类外不能访问 -> 儿子拿不到


 struct和class 区别：

> struct -> 默认权限为public:    
> class -> 默认权限是private:


将成员属性设为私有

好处：
1. 可以自己控制读写的权限      
2. 对于写权限，我们可以检查数据的有效性

~~~ c 
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
        //在这里加条件 可以控制数据的有效性
        m_name = name;
    } //只写 
    string get_name(){
        return m_name;
    } //只读

};


int main()
{
    person p;
    p.set_name("张三");
    // p.m_name = "张三"; //不能这样写权限不足
    cout << p.get_name() << endl;
}
~~~

### 初始化和清理

#### 构造函数和析构函数

这两个函数是编译器提供 （可写可不写） ——> 空实现


1. 构造函数： 主要作用在于创建对象时赋值，构造函数由编译器自动调用
   
2. 析构函数： 主要主用在于对象`销毁前`系统自动调用清理工作


>构造函数语法： 类名(){}      
1.  没有返回值，也不写void
2.  类名于函数名相同
3.  构造函数也有参数，因此可以发生重载
4.  程序在调用对象时候会自动调用构造，无需手动调用，只会来一次


>析构函数语法 ~类名(){}

1. 也没有返回值，不写void 
2.  类名于函数名相同，前面加~
3. 析构函数不能有参数，没重载
4. 程序销毁对象时自动析构

~~~cpp
#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    int age;
    // string name;
    Person()
    {
        cout << "无参构造函数" << endl; // 如果不写这个函数，系统空实现（什么都没有）
    }
    Person(int a)
    {
        cout << "有参构造" << endl;
        age = a;
    }
    Person(const Person &p)
    { // 以引用的方式传入
        age = p.age;
        cout << "拷贝构造" << endl;
    }
    ~Person()
    {
        cout << "析构函数" << endl;
    }
};
void test01()
{             // 1括号法
    Person p; // 在栈上的数据，所以销毁对象

    // 不要写 Person p(); -> 编译器会认为函数的声明
    Person p2(10);
    Person p3(p2);
    cout << p2.age << "  " << p3.age << endl;
}
void test02()
{
    // 显示法
    Person p1;
    Person p2 = Person(10); // 调用有参 ->匿名对象
    Person p3 = Person(p2); // 拷贝
    cout << p2.age << "  " << p3.age << endl;
}
void test03() {
    //隐式转换
    Person p1 = 10;
    Person p2 = p1;
     cout << p1.age << "  " << p2.age << endl;
}
int main()
{

    // test01();
    // test02();
    test03();
}
~~~

#### 构造函数分类

如上代码块

#### 拷贝构造函数调用时机

1. 使用一个已经创建完毕的对象来初始化另外一个新对象‘
2. 值传递的方式给函数参数传值
3. 以值方式返回局部对象

#### 深拷贝与浅拷贝

1. 浅拷贝：简单的赋值操作
2. 深拷贝：在堆区重新申请空间，进行拷贝操作

~~~ cpp
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
~~~

#### 初始化列表

作用：c++提供初始化列表语法

语法： 构造函数():属性1(值),属性2(值)... {}

~~~cpp

class  Person {
    public:
    int M_a;
    int M_b;
    int M_c;
    // Person (int a,int b ,int c){
    //     M_a=a;
    //     M_b=b;
    //     M_c=c;
    // }//初始

//初始化列表
    Person(int a,int b ,int c):M_a(a),M_b(b),M_c(c){} 

}

~~~

#### 类作物一个成员

~~~ cpp
class Phone{
    public:
    string p_Name;
    Phone(string p_name){
        p_Name =p_name;
    }
}


class Person{
public:

string m_name;

Phone m_phone;
Person(string name,string phone ): m_name(name),m_phone(phone){

}

};


~~~

