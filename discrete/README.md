# 离散化

## 原理

离散化与其说是一个算法而言，更应该被称为是一种技巧，可能在一些情况下，数据量较小但是数值很大，这个时候我们可以对齐进行离散化，将数值映射到其一个更小的区间内，如下所示

[1, 1000, 40000] -> [1, 2, 3]

## 代码实现

先对数据进行排序，然后使用unique函数去除重复的数值，再通过二分查找的形式找到其对应在离散空间中的位置，如下所示

```cpp
vector<int> points;
for (int i = 0; i < events.size(); i++) {
    points.push_back(events[i][0]-1);
    points.push_back(events[i][1]);
}
sort(points.begin(), points.end());
int len = std::unique(points.begin(), points.end()) - points.begin();
for (int i = 0; i < events.size(); ++i)  {
    events[i][0] = lower_bound(points.begin(), points.end() + len, events[i][0]-1) - points.begin();
    events[i][1] = lower_bound(points.begin(), points.end() + len, events[i][1]) - points.begin();
}
```
