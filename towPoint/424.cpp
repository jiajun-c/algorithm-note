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