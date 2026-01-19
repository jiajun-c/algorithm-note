#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> sum(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mat[i - 1][j - 1];
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int currentLen = ans + 1;
                if (i < currentLen || j < currentLen) continue;
                int s= sum[i-currentLen][j - currentLen] - sum[i][j-currentLen] - sum[i-currentLen][j] + sum[i][j];
                if (s <= threshold) {
                    ans++;
                }
            }
        }
        return ans;
    }
};