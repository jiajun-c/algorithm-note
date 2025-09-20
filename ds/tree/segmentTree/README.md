# 线段树

线段树是一种数据结构，用来存储区间信息，支持对区间的修改，查询。

进行线段树的初始化，第一个节点表示l到r的区间，第二个节点和第三个节点分别表示l到r中的前半部分和后半部分区间。

```cpp
    void build(int l, int r, int p) {
        if (l == r) {
            data[p] = a[l];
            return;
        }
        int m = l +((r - l)>>1);
        build(l, m, p*2);
        build(m+1, r, p*2+1);
    }
```

进行区间更新时，我们可以使用一个lazy数组来表示对当前区间的更新缓存，来减少递归的更新。

```cpp
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
```

进行区间数据的查询

```cpp
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
```