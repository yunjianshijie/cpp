#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

int main() {
    int N;
    cin >> N;
    
    unordered_map<int, int> tang;
    
    for (int i = 0; i < N; i++) {
        int number, color;
        cin >> number >> color;
        
        if (tang.find(color) == tang.end()) {
           tang[color] = number;
        } else {
           tang[color] = min(tang[color], number);
        }
    }
    
    int max1 = INT_MIN;
    
    // 找到最大的最小美味度
    for (const auto& entry : tang) {
        max1 = max(max1, entry.second);
    }
    
    cout << max1 << endl;
    
    return 0;
}