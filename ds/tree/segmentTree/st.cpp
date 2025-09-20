#include <iostream>
#include <vector>

using namespace std;

class st {
public:
    vector<int>data;
    vector<int>lazy;
    int *a;
    st(int n, int *_a) {
        data = vector<int>(n, 0);
        lazy = vector<int>(n, 0);
        a = _a;
    }

    void build(int l, int r, int p) {
        if (l == r) {
            data[p] = a[l];
            return;
        }
        int m = l +((r - l)>>1);
        build(l, m, p*2);
        build(m+1, r, p*2+1);
    }
    void pushDown(int s, int t, int p) { 
        int m = (s + ((t - s)>>1));
        if (lazy[p]) {
            data[p*2] += lazy[p] * (m - s + 1);
            data[p*2+1] += lazy[p] * (t - m);

            lazy[p*2] += lazy[p];
            lazy[p*2+1] += lazy[p];
            lazy[p] = 0;
        }
    }
    void update(int l, int r, int val, int s, int t, int p) {
        if (s >= l && t <= r) {
            data[p] += val * (t - s + 1);
            lazy[p] += val;
            return;
        }
        int m = s +((t - s)>>1);
        pushDown(s, t, p);
        if (l <= m) update(l, r, val, s, m, p*2);
        if (r > m) update(l ,r, val, m+1, t, p*2+1);
    }
    int getSum(int queryl, int queryr, int l, int r, int p) {
        if (queryl <= l && queryr >= r) {
            return data[p];
        }
        pushDown(l, r, p);
        int m = l +((r - l)>>1), sum = 0;
        if (queryl <= m) sum += getSum(queryl, queryr, l, m, p*2);
        if (queryr > m) sum += getSum(queryl, queryr, m+1, r, p*2+1);
        return sum;
    }



};