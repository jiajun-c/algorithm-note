#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int maxDay = -1;
        for (auto day: bloomDay) {
            maxDay = max(day, maxDay);
        }
        int l = 1;
        int r = maxDay;
    }
};