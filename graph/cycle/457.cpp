class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        auto next = [&](int i) {
            return ((i + nums[i]) % n + n) % n;
        };
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) continue;
            int slow = i, fast = next(i);
            while (nums[slow] * nums[fast] > 0 && nums[fast] * nums[next(fast)] > 0) {
                if (slow == fast) {
                    if (slow == next(slow)) break;
                    return true;
                }
                slow = next(slow);
                fast = next(next(fast));
            }
            int val = nums[i], j = i;
            while (nums[j] * val > 0) {
                int temp = next(j);
                nums[j] = 0;
                j = temp;
            }
        }
        return false;
    }
};