#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>q;
        int n = nums.size();
        vector<int>curIdx(n, 1);
        int end = INT32_MAX;
        for (int i = 0; i < n; i++) {
            q.push(make_pair(nums[i][0], i));
            end = max(end, nums[i][0]);
        }
        int start = q.top().first;
        vector<int>ans = {start, end};
        while (!q.empty()) {
            auto top = q.top();
            q.pop();
            int idx = top.second;
            int next = curIdx[idx];
            if (next < nums[idx].size()) {
                q.push({nums[idx][next], idx});
                end = max(end, nums[idx][next]);
                if (end - start < ans[1] - ans[0]) {
                    ans[0] = start;
                    ans[1] = end;
                } else if (end - start  == ans[1] - ans[0] && start < ans[0]) {
                    ans[0] = start;
                    ans[1] = end;
                }
                curIdx[idx]++;
            } else {
                break;
            }
        }
        return ans;
    }
};