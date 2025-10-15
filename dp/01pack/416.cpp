class Solution {
    public:
        bool canPartition(vector<int>& nums) {
            int sum = 0;
            for (auto num: nums) sum += num;
            if (sum%2) return false;
            vector<int>dp(sum, 0);
            dp[0] = 1;
            for (int i = 0; i < nums.size(); i++) {
                for (int j = sum/2; j >= nums[i]; j--) {
                    dp[j] = dp[j] || dp[j-nums[i]];
                }
            }
            return dp[sum/2];
        }
    };