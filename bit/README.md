# 位运算相关

在算法设计中经常会遇到空间不足的问题，这时候可以借助"拆位"的方式进行解决，单独计算每个bit位给结果带来的影响，可以解决如某个子区间内，所有元素对的一些操作

如NC269155，如果暴力计算的话，其需要的时间复杂度为O(n^4)，空间复杂度为O(n)，针对n为1e5量级的数据，我们应该考虑32*n时间复杂度的算法

如下所示，第二个维度遍历每个bit位

```cpp
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
```