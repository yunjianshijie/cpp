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
~~~ cpp
empty();
capacity();
size();
resize(int num);
resize()

~~~

```cpp
std::map<KeyType, ValueType> myMap;
std::map<std::string, int> ages = {
    {"Alice", 25}, {"Bob", 30}, {"Charlie", 35}
};
//便厉
for (const auto& pair : myMap) {
    std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
}

```

myMap.size(): 返回容器中元素的个数
myMap.empty(): 检查容器是否为空
myMap.find(key): 返回指向给定键的迭代器,如果找不到则返回 myMap.end()
myMap.count(key): 返回给定键出现的次数(0 或 1)
``` cpp
auto it = myMap.find(key);
if (it != myMap.end()) {
    // key 存在,可以安全地访问值
    int value = it->second;
} else {
    // key 不存在,进行相应的错误处理
}
```
``` cpp
    try{
    int value = myMap.at(key);
    // 使用 value
   } catch (const std::out_of_range& e) {
    // 处理异常,例如打印错误信息
    std::cerr << "Error: " << e.what() << std::endl;
}
```