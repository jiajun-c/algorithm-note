#include <iostream>
#include <vector>
#include <queue>

using namespace std;
class Solution {
public:
    using pr = pair<int, int>;
    int shortestSubarray(vector<int>& nums, int k) {
        priority_queue<pr, vector<pr>, greater<pr>>pq;
        vector<int>pre(nums.size(), 0);
        pre[0] = nums[0];
        int ans = nums.size() + 1;
        for (int i = 1; i < nums.size(); i++) {
            pre[i] = pre[i-1] + nums[i];
        }
        for (int i = 0; i < nums.size(); i++) {
            int now = pre[i];
            while(!pq.empty() && now - pq.top().first >= k) {
                ans = min(ans, i - pq.top().second);
                pq.pop();
            }
            pq.push({pre[i], i});
        }
        return ans == nums.size() + 1 ? -1 : ans;
    }
};