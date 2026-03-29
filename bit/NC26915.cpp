#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
const int mod = 1e9 + 7;
long long cnt[30][2];
int n;
int a[200005];
long long ans = 0;
void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 30; j++) {
            int k = (a[i] >> j) & 1;
            ans = (ans + (1ll<<j) * cnt[j][k^1]%mod * 2%mod * (n - i + 1)%mod)%mod;
            cnt[j][k] = (cnt[j][k] + i)%mod;
        }
    }
    printf("%lld\n", ans);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    solve();
}