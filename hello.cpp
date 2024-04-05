#include <iostream>
#include <string>
using namespace std;
#define MAX 5
int main()
{
    // cout << "输入一个文本";
    // char p;
    // while (cin.peek() != '\n')//peek 检查，
    // {
    //     p = cin.get();
    //     cout << p;
    // }
    // // cout << '\n';
    // auto x2 =0;
    // x2 = 0;
    // cout << x2 << '\n';
    // cin >> x2;
    // cout << "x2="<< x2 << '\n';
    // //cin.get();//这里是'\n'

    // //cin.ignore(100, '\n'); //hu
    // cin.clear();
    // //提供cin.string可以实现
    string str ="hello";
    string str1 = "world";
    string str2 = str + str1 + "  ";
    // cout << "~~~" << '\n';//用getline 能=
    // cin >> str;
    // getline(cin, str);
    str2.append(str);
    string str11[MAX];
    cout << reinterpret_cast<unsigned long>(str11) << endl;
    cout << str11  << endl;
    // int len1;
    // cin >> len1;
    // getline(std::cin, str);//这个可以只看到 \n
    auto len = str2.length();
    string str3 = str.substr(1, 4);
    cout << len << " " << str3 << " " << endl;

    

    return 0;

}