#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int>dq;
        vector<int>res(nums.size() - k + 1);
        for (int i = 0; i < nums.size(); i++) {
            int j = i - k + 1;
            if (j >= 1 && deque.front() == nums[j-1]) {
                dq.pop_front();
            }
            while (!dq.empty() && dq.back() < nums[i])
            {
                dq.pop_back();
            }
            dq.push_back(nums[i]);
            if (j >= 0)
            res[j] = dq.front();
        }
        return res;
    }
};