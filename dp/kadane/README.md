# 卡丹算法

卡丹算法可以用于计算数组中的最大的连续数组，相比于使用dp算法而言，可以在O(1)时间内完成计算。

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // memset(dp, 0, sizeof dp);
        int now = nums[0];
        int ans = nums[0]; 
        for (int i = 1;i < nums.size();i++) {
            // dp[i] = nums[i] + max(dp[i-1],0);
            now = max(now + nums[i], nums[i]);
            ans = max(ans, now);
        }
        return ans;
    }
};
```