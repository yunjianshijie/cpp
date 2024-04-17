#include <iostream>
#include <string>
using namespace std;
int main()
{
    string b;
    cin >> b;
    int n = b.size();
    int find[30] = {0};
    for (int i = 0; i < n; i++)
    {
        find[b[i] - 'a']++;
    }
    int ji = 0;
    int count = 0;
    int h[100] = {0};
    for (int i = 0; i < 30; i++)
    {
        if (find[i] != 0)
        {
            h[find[i]]++;
        }
    }
    for (int i = 0; i < 100; i++)
    {
        if (h[i] != 0 && h[i] != 2)
        {
            cout << "No";
            return 0;
        }
    }
    cout << "Yse";
    return 0;
}