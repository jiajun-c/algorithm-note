#include <cstdio>
#include <iostream>
#include <vector>
const int N = 2e5 + 10;
using namespace std;

int n, k;
int v[N], w[N];
int main() {
    scanf("%d %d\n", &n, &k);
    for (int i = 0; i <= n; i++) {
        scanf("%d %d\n", &v[i], &w[i]);
    }
    int res = 0;
    for (int i = 30; i >= 0; i--) {
        int tempans = res | (1 << i);
        int vol = -1;
        for (int j = 0; j < n; j++) {
            if ((tempans & w[j]) == tempans) {
                if (vol == -1) {
                    vol = v[i];
                } else {
                    vol = vol & v[i];
                }
            }
            if (vol != -1 && vol <= k) {
                res = tempans;
            }
        }
    }
    printf("%d\n", res);
}