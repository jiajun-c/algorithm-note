#include <__clang_cuda_runtime_wrapper.h>
#include <iostream>
#include <utility>
#include <vector>

class Solution
{
public:
    int findKthNumber(int m, int n, int k)
    {
        int l = 1;
        int r = m*n;
        if (m > n) std::swap(m ,n);
        while (l < r) {
            int mid = (l + r)>>1;
            int temp = 0;
            for (int i = 1; i <= m; i++) {
                temp += min(n, mid/i);
            }
            if (temp < k) {
                l = mid+1;
            } else {
                r = mid;
            }
        }
        return l;
    }
};