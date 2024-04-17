#include<iostream>

int main(){
    int n;
    std::cin >> n;
    int sum=0;
    int count=0;
    for (int i = 0; i < n-1; i++)
    {
        std::cin >> count;
        sum -= count;
    }
    std::cout << sum;
    return 0;
}