auto 优先选用auto,而非显式型声明


~~~cpp
#include<iostream>
using namespace std;
int main(){
    auto x1 =0;//这个可以
    auto x2 ;//这个不可以
}
~~~


