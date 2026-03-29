# 双指针问题

使用双指针可以解决区间问题，如满足特定约束的区间最大长度，双指针由左右两个指针组成，右指针负责入队伍，左指针负责出队，当满足约束的时候，右侧指针增长，不满足约束的时候，左侧指针进行出队。

[leetcode 424](https://leetcode.com/problems/longest-repeating-character-replacement/description/)

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        int ans = min(n, k);
        for (char now = 'A'; now <= 'Z'; now++) {
            int i = 0, j = 0, replace = 0;
                while (j < n) {
                if (s[j] == now) {
                    j++;
                } else if (replace < k) {
                    j++;
                    replace++;
                } else if (s[i] == now) {
                    i++;
                } else {
                    i++;
                    replace--;
                }
                ans = max(ans, j - i + 1);
            }
        }
        return ans;
    }
};
```