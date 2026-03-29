#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minimumPairRemoval(vector<int>& a) {
        vector<long long>nums;
        for (auto x: a) {
            nums.push_back(x);
        }
        int neg = 0;
        int n = nums.size();
        for (int i = 0; i < n - 1; i++) {
            if (nums[i] > nums[i+1]) neg++;
        }
        vector<int>l(n, -1);
        vector<int>r(n, -1);
        for (int i = 0; i < n; i++) {
            l[i] = i-1;
            r[i] = (i+1 < n) ? i+1 : -1; 
        }
        using pi = pair<int, int>;
        priority_queue<pi, vector<pi>, greater<pi>>heap;
        for (int i = 0; i < n - 1; i++) {
            heap.push({nums[i] + nums[i+1], i});
        }
        auto bad = [&](int x, int y) {
            return nums[x] > nums[y];
        };
        int ans = 0;
        while (neg) {
            auto [v, i] = heap.top(); heap.pop();
            int ridx = r[i];
            if (ridx == -1) continue;
            if (l[ridx] != i) continue;
            if (nums[i] + nums[ridx] != v) continue;

            int lidx = l[i];
            int rridx = r[ridx];
            if (lidx != -1 && r[lidx] == i && bad(lidx, i)) neg--;
            if (bad(i, ridx)) neg--;
            if (rridx != -1 && l[rridx] == ridx && bad(ridx, rridx)) neg--;

            nums[i] = v;
            r[i] = rridx;
            if (rridx != -1) l[rridx] = i;
            l[ridx] = r[ridx] = -1;

            if (lidx != -1 && r[lidx] == i && bad(lidx, i)) neg++;
            if (rridx != -1 && l[rridx] == i && bad(i, rridx)) neg++;

            if (lidx != -1 && r[lidx] == i) heap.push({nums[lidx] + nums[i], lidx});
            if (rridx != -1 && l[rridx] == i) heap.push({nums[i] + nums[rridx], i});
            ans++;
        }
        return ans;
    }
};