#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;
int n, p;
const int N = 1e6+10;
int a[N], b[N];
int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x%y);
}
void solve() {
    // unordered_set<int>s;
    vector<int>need(p, 0);
    int maxCount = -1;
    for (int i = 0; i < n; i++) {
        int add = (b[i] - a[i]%p + p) % p;
        need[add]++;
        // s.insert(need[i]);
    }
    int ans = p+1;
    int ansx = -1;
    for (int i = 0; i < p; i++) {
        int nowans = 0;
        vector<int>times(p, 1e9);
        for (int j = 0; j < p; j++) {
            times[j*i%p] = min(times[j*i%p], j);
            printf("%d %d %d\n",i, j*i%p, times[j*i%p]);
        }

        for (int j = 0; j < p; j++) {
            if (need[j] == 0) continue;
            nowans = max(nowans, times[j]);
        }
        if (nowans < ans) {
            ans = nowans;
            ansx = i;
        }
    }
    // printf("%d\n", gcdx);
    printf("%d\n", ansx);
}
int main() {
    // printf("dede\n");
    // printf("%d\n", gcd(2, 4));
    cin >> n >> p;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int j = 0; j < n; j++) cin >> b[j];
    solve();    
}