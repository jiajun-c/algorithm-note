#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestSubstring(string s, int k) {
        vector<vector<int>>pos(26, vector<int>());
        int n = s.size();
        vector<vector<int>>prefix(s.size(), vector<int>(26, 0));
        prefix[0][s[0] - 'a']++;
        for (int i = 1; i < s.size(); i++) {
            for (int j = 0; j < 26; j++) {
                prefix[i][j] = prefix[i-1][j];
            }
            prefix[i][s[i] - 'a']++;
            pos[s[i]-'a'].push_back(i);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int j = n-1;
            while (j >= i) {
                int found = 1;
                for (int c = 0; c < 26; c++) {
                    int fq = prefix[j][c];
                    if (i > 0) {
                        fq -= prefix[i-1][c];
                    }
                    if (fq > 0 && fq < c) {
                        found = 0;
                        int idx = lower_bound(pos[c].begin(), pos[c].end(), i) - pos[c].begin();
                        j = min(j, pos[c][idx]-1);
                    }
                }
                if (found) {
                    ans = max(ans, j - i + 1);
                    break;
                }
            }
        }
        return ans;
    }
};