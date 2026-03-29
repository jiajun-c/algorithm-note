#include <iostream>
#include <vector>
using namespace std;
int n, m, k;
const int N = 3e3 + 10;
int dp[N][N];
int dp1[N][N];
int a[N];
int main() {
    
    std::cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    // dp[0][0] = a[0];
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= min(i, k); j++) {
            if (j == 0) {
                dp[i][j] = dp[i-1][j] + a[i];
            } else {
                dp[i][j] = min(dp[i-1][j] + a[i], dp[i-1][j-1]/2);
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        dp1[i][0] = dp[i-1][0] + a[i]; 
    }
    for (int i = m; i <= n; i++) {
        for (int j = 0; j <= min(i, k); j++) {
            if (j == 0) {
                dp1[i][j] = dp[i-1][j] + a[i];
            } else {
                int start = max(0, i - m);
                dp1[i][j] = min(dp1[i-1][j] + a[i], dp1[start][j-1]);
            }
        }
    }
    for 
    int ans = INT32_MAX;
    for (int j = 0; j <= k; j++) {
        ans = min(ans, min(dp[n][j], dp1[n][j]));
    }
    printf("\n%d\n", ans);
}