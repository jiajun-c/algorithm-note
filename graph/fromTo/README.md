# from To 问题解决模式

经典的格式就是有个from to weight，表示从哪里到哪里，权重有多少。

针对这点可以建立一个edge结构体

```cpp
struct Edge {
    int from;
    int to
};
```

然后使用一个`vector<Edge>edges`数组去存储这个点对应的边的信息。

再使用一个数组去保存入度和出度。