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







