#include <iostream>
#include <vector>
using namespace std;
void backtrace(int n, int dep,vector<int>&now, vector<string>&v) {
    // printf("%d %d\n",n,dep);
    if (dep == n) {
        string s = "";
        for (int i = 0; i < n; i++) s += to_string(now[i]);
        std::cout << s << "\n";
        v.push_back(s);
        return;
    }
    for (int i = dep; i < n; i++) {
        std::swap(now[i], now[dep]);
        backtrace(n, dep+1, now, v);
        std::swap(now[i], now[dep]);
    }
}
int main() {
    std::vector<string>s;
    std::vector<int>v;
    for (int i = 0; i < 4; i++) v.push_back(i);
    backtrace(3, 0, v, s);
    printf("%d\n", s.size());
}