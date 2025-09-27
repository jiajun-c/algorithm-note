# 几何学

## 面积公式

三角形面积公式：

S(ABC) = 1/2 * |(Bx-Ax)(Cy-Ay)-(By-Ay)(Cx-Ax)|

## 凸包

凸包算法是用于计算多个点组成的多边形的最小周长。先计算下凸壳，再计算上凸壳，通过单调栈的形式对结果进行更新。

在凸壳的计算过程中，通过判断边的角度是否为负数来决定其是否应该被抛弃，而选择新的点进行加入，上下凸壳的方向相反，所以需要反向遍历。

```cpp
            vector<int2> pts(n);
            for(int i=0; i<n; i++) pts[i]={points[i][0], points[i][1]};
            sort(pts.begin(), pts.end());
            vector<int2> hull(2*n);
            int k = 0;
            for (int i = 0; i < n; i++) {
                while (k >= 2&& cross(hull[k-2], hull[k-1], pts[i]) <= 0) {
                   k--;
                }
                hull[k++] = pts[i];
            }

            for (int i = n-1, t = k+1; i >= 0; i--) {
                while (k >= t && cross(hull[k-2], hull[k-1], pts[i]) <= 0) {
                    k--;
                }
                hull[k++] = pts[i];
            }
```

