#include <iostream>
#include <algorithm>
using namespace std;
void fastsort(int *a, int l, int r) {
    if (l >= r) return;
    int mid = (l + r)>>1;
    int i = l-1, j = r + 1;
    int base = a[mid];
    while (true)
    {
        while (a[--j] > base);
        while (a[++i] < base);
        if (i < j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        } else {
            break;
        }
    }
    fastsort(a, l, i-1);
    fastsort(a, i+1, r);
}

int main() {
    int a[10] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
    fastsort(a, 0, 8);
    for (int i = 0; i < 9; i++) {
        printf("%d ", a[i]);
    }
}