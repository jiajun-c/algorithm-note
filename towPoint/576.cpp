#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool checkInclusion(string s, string p) {
        vector<int>pcount(26, 0);
        for (auto c : p) pcount[c-'a']++;
        vector<int>win(26, 0);
        vector<int>ans;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int can = true;
            for (int j = 0; j < 26; j++) {
                if (win[j] != pcount[j]) {
                    can = false;
                    break;
                }
            }
            win[s[i] - 'a']++;
            if (i >= p.size()) {
                win[s[i] - p.size()]--;
            }
            if (can) {
                return true;
            }
        }
        return false;
    }
};