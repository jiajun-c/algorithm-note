#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int>pos[26];
        int n = s.length();
        vector<vector<int>>perfix(26, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'A';
            perfix[c][i]++;
            for (int i = 0; i < 26; i++) {
                if (i > 0) {
                    perfix[c][i] += perfix[c][i-1];
                }
            }
            pos[c].push_back(i);
        }

        int ans = min(n, k);
        for (int i = 0; i < n; i++) {
            int j = n-1;
            while (j-k + 1 >= i) {
                int len = j - i + 1;
                int found = 0;
                for (int c = 0; c < 26; c++) {
                    int fq = perfix[c][j];
                    if (i > 0) fq -= perfix[c][i-1];
                    if (fq >= len - k) {
                        found = 1;
                        ans = max(ans, len);
                        break;
                    }
                    if (fq > k) {

                    }
                }
                if (found) break;
            }
        }
        return ans;
    }
};