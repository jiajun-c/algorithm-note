#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
    #define N 10000
    #define mod 1000000007
class Solution {
public:

    long long x[N];
    struct query {
        long long l, r;
        long long h;
        int add;
    }q[N];
    static bool cmp(query &x, query &y) {
        return x.h < y.h;
    }
    struct node {
        long long l, r;
        int lazy;
        long long sum;
    }Nodes[N];
    void build(int l, int r, int idx) {
        Nodes[idx].l = l;
        Nodes[idx].r = r;
        Nodes[idx].lazy = Nodes[idx].sum = 0;
        if (l == r) return;
        int mid = l + ((r - l)>>1);
        build(l, mid, idx*2);
        build(mid+1, r, idx*2+1);
    }

    void pushup(int idx) {
        if (Nodes[idx].lazy) {
            Nodes[idx].sum = x[Nodes[idx].r + 1] - x[Nodes[idx].l];
        } else if (Nodes[idx].l == Nodes[idx].r) {
            Nodes[idx].sum = 0;
        } else {
            Nodes[idx].sum = (Nodes[idx*2].sum + Nodes[idx*2+1].sum)%mod;
        }
    }
    void update(int queryl, int queryr, int adder, int idx)  {
        if (queryl <= Nodes[idx].l && queryr >= Nodes[idx].r) {
            Nodes[idx].lazy += adder;
            pushup(idx);
            return;
        };
        int mid = Nodes[idx].l + ((Nodes[idx].r - Nodes[idx].l)>>1);
        if (queryl <= mid) update(queryl, queryr, adder, idx*2);
        if (queryr > mid) update(queryl, queryr,  adder,  idx*2+1);
        pushup(idx);
    }

    int rectangleArea(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        for (int i = 0; i < n; i++) {
            x[i*2] = rectangles[i][0];
            x[i*2+1] = rectangles[i][2];
            q[i*2] = query{rectangles[i][0], rectangles[i][2], rectangles[i][1], 1};
            q[i*2+1] = query{rectangles[i][0], rectangles[i][2], rectangles[i][3], -1};
        }
        sort(x, x+n*2);
        sort(q, q+n*2, cmp);
        int k = unique(x, x+n*2) - x;
        build(0, k, 1);
        long long ans = 0;
        for (int i = 0; i < 2*n; i++) {
            int l = lower_bound(x, x+k, q[i].l) - x;
            int r = lower_bound(x, x+k, q[i].r) - x - 1;
            update(l, r, q[i].add, 1);
            ans += Nodes[1].sum * (q[i+1].h - q[i].h);
            ans %= mod;
        }
        return ans;
    }
};