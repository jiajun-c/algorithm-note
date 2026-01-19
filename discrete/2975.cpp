#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
const int mod = 1000000009;
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());

        vector<int>newhFences, newVFences;
        newhFences.push_back(1);
        newVFences.push_back(1);
        for (auto h: hFences) newhFences.push_back(h);
        for (auto v: vFences) newVFences.push_back(v);
        newhFences.push_back(m);
        newVFences.push_back(n);
        unordered_set<int>setH;
        for (int i = 0; i < newhFences.size(); i++) {
            setH.insert(newhFences[i+1] - newhFences[i]);
        }
        int nowH = hFences[0];
        for (int i = 0; i < newhFences.size(); i++) {
            for (int j = 0; j < i; j++) {
                setH.insert(newhFences[i] - newhFences[j]);
            }
        }
        long long maxLine = -1;
        for (int i = 0; i < newVFences.size(); i++) {
            for (int j = 0; j < i; j++) {
                int now = newVFences[i] - newVFences[j];
                if (setH.find(now) != setH.end()) {
                    maxLine = max(maxLine, (long long)now);
                }
            }
        }
        long long res = (maxLine%mod)*(maxLine%mod)%mod;
        return res;
    }
};