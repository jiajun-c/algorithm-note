#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class Solution {
public:
    using pr = pair<int, int>;
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        priority_queue<pr, vector<pr>, greater<pr>>pq1, pq2, pq3;
        vector<int>ans = {0, k, 2*k};
        int n = nums.size();
        vector<int>prefix(n, 0);
        prefix[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i-1] + nums[i];
        }
        int curMax = -1;
        vector<int>kprefix(n-k+1, 0);
        kprefix[0] = prefix[k-1];
        for (int i = 1; i < n-k + 1; i++) {
            kprefix[i] = prefix[i+k-1] - prefix[i-1];
        }
        // 第一个的最大值
        vector<pr>lprefix(n, {0, 0});
        vector<pr>rprefix(n, {0, 0});
        lprefix[0] = {kprefix[0], 0};
        for (int i = 1; i <= n-3*k; i++) {
            lprefix[i] = {kprefix[i], i};
            if (lprefix[i].first <= lprefix[i-1].first) {
                lprefix[i] = lprefix[i-1];
            }
        } 
        rprefix[n-k] = {kprefix[n-k], n-k};

        for (int i = n - k-1; i >= 2*k; i--) {
            rprefix[i] = {kprefix[i], i};
            if (rprefix[i].first < rprefix[i+1].first) {
                rprefix[i] = rprefix[i+1];
            }
        }
        for (int i = k; i <= n-2*k; i++) {
            int cur2 = prefix[i + k -1] - prefix[i - 1];
            int cur1Idx = i - k;
            int cur3Idx = i + k;
            int nowMax = cur2 + lprefix[cur1Idx].first + rprefix[cur3Idx].first;
            if (nowMax > curMax) {
                curMax = nowMax;
                ans = {lprefix[cur1Idx].second, i, rprefix[cur3Idx].second};
            }
        }
        return ans;
    }
};