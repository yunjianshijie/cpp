class Solution
{
public:
    int longestSubarray(vector<int> &nums)
    {
        // int n = nums.size();
        // int ans = 0;
        // int max1 = 0;
        // int qian = 0;
        // int hou = 0;
        // int ii = 0;
        // int r = 0;
        // int i = 0;
        // if(find(nums.begin(),nums.end(),0)==nums.end()){
        //     return  n-1;
        // }
        // while (i < n && r < n) { //
        //     i = ii;

        //     if (i != 0) {
        //         qian = hou;
        //         hou = 0;
        //     }
        //     while(nums[i]==0){
        //         hou=qian=0;
        //         i++;
        //     }
        //     ii = r;
        //     while (r < n && nums[r++] != 0) {
        //         hou++;
        //     }
        //     ans = max(ans, qian+hou);
        // }
        // return ans;

        int l = 0;
        int ans = 0;
        int cont = 0;
        for (int r = 0; r < nums.size(); r++)
        {
            cont += 1 - nums[r];
            if (cont > 1)
            {
                cont -= 1 - nums[l++];
            }
            ans = max(ans, r - l);
        }
        return ans;
    }
};