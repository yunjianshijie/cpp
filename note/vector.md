# 

vector 可以动态扩展

~~~ cpp
#include <vector>
vector<T> v; //默认构造函数
vector<T> v2(v.begin(),v.end());//拷贝函数 直接传迭代器
vector<T> v3(n,elem)//n个elem 
vertor<T> v4(v); //拷贝
~~~

## 赋值

1. 等号赋值
2. assign 

~~~cpp
vector<int>v3;
v3.assgin(v1.begin(),v1.end()); //和构造差不多
v4.assgin(10,100);
~~~
## 容量大小操作

empty();
capacity();
size();
resize(int num);
resize()

~~~


