#include <iostream>
#include <vector>
using namespace std;
string s;
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
int dp[N][2][2];
void solve() {
    int n = s.size();
    dp[0][0][1] = dp[0][0][0] = 1;
    s = " " + s;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '0') {
            dp[i][0][0] = dp[i-1][0][0];
        } else if (s[i] == '1') {
            dp[i][0][1] = dp[i-1][0][0];
            dp[i][0][0] = dp[i-1][1][0];
        } else if (s[i] == '2') {
            dp[i][1][1] = dp[i-1][1][0];
        } else if (s[i] == '*') {
            dp[i][1][0] = dp[i-1][0][1] + dp[i-1][1][1];
            dp[i][1][1] = dp[i-1][0][1] + dp[i-1][1][1];
            dp[i][1][0] %= mod;
            dp[i][1][1] %= mod;
        } else if (s[i] == '?') {
            dp[i][0][0] = dp[i-1][1][0] + dp[i-1][0][0];
            dp[i][0][1] = dp[i-1][1][0] + dp[i-1][0][0];
            dp[i][1][0] = dp[i-1][0][1] + dp[i-1][1][1];
            dp[i][1][1] = dp[i-1][0][1] + dp[i-1][1][1];
            dp[i][0][0] %= mod;
            dp[i][0][1] %= mod;
            dp[i][1][0] %= mod;
            dp[i][1][1] %= mod;
        }
    }
    printf("%d\n", (dp[n][1][0] + dp[n][0][0])%mod);
}
int main() {
    std::cin >> s;
    solve();
}