#include <iostream>
#include <thread>

using namespace std;


template<typename T>
void myswap(T& a,T&b ){
   T temp=a;
   a=b;
   b=temp;
}
void test01(){
   int a=0;
   int b=1;
   char c = 'c';
   myswap(a, b);
   //
   //myswap(a, c);//错误
   
   cout << "a =" << a << " b= " << b << endl;
   myswap<int>(a,b);
    cout << "a =" << a << " b= " << b<< endl;
}

int main(){
    test01();

}