#include <iostream>
#include <vector>
int n;
using namespace std;
vector<int>edge[110000];
vector<int>value(11000, 0);
int cnt(int x) {
    int k = 0;
    for (int i = 2; i*i <= x; i++) {
        while (x%i == 0) {
            x /= i;
            k++;
        }
    }
    if (x > 1) k++;
    return k;
}

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x%y);
}
int ans = 0;
void dfs(int now, int fa) {
    for (auto to: edge[now]) {
        if (to == fa) continue;
        dfs(to, now);
        int g = gcd(value[now], value[to]);
        ans += cnt(g);
        value[now] /= g;
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> value[i];
    }
    for (int i = 0; i < n-1; i++) {
        int from, to;
        cin >> from >> to;
        edge[from].push_back(to);
        edge[to].push_back(from);
    }
    dfs(1, 0);
    printf("%d\n", ans);
}