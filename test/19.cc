#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    vector<int> temp;
    vector<vector<int>> ans;

    void dfs(int cur, int n, int k, int sum) {
        //已经记录的数据个数加上剩余的数的个数小于需要的个数时返回（此时一定不满足要求
        //已经记录的的数的个数大于k时返回（不符合题意
        if (temp.size() + (n - cur + 1) < k || temp.size() > k) {
            return ;
        }
        //满足题意的数据写入ans
        if (temp.size() == k && accumulate(temp.begin(), temp.end(), 0) == sum) {
            ans.push_back(temp);
            return ;
        }

        temp.push_back(cur);
        dfs(cur + 1, n, k, sum);
        temp.pop_back();
        dfs(cur + 1, n, k, sum);
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        dfs(1, 9, k, n);
        return ans;
    }
};

int main(){
    int k = 3;
    int n = 7;
    Solution a;
    a.combinationSum3(k,n);
}