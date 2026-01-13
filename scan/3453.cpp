#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Solution {
public:
    static inline uint64_t pack(uint64_t y, uint64_t L, bool istart) {
        return y << 32 | L << 1 | istart;
    }
    double separateSquares(vector<vector<int>>& squares) {
        const int n = squares.size();
        vector<uint64_t>events;
        double fullSize = 0.0;
        for (int i = 0; i < n; i++) {
            int y = squares[i][1];
            int l = squares[i][2];
            fullSize += l * l;
            events.push_back(pack(y, l, 1));
            events.push_back(pack(y+l, l, 0));
        }
        double halfSize = fullSize/2.0;
        double nowSize = 0.0;
        sort(events.begin(), events.end());
        double width = 0.0, prevY = 0.0;
        for (int i = 0; i < n*2; i++) {
            uint64_t event = events[i];
            int y=event>>32, L=(event&UINT_MAX)>>1, dy=y-prevY;
            double curA = dy * width;
            if (nowSize + curA >= halfSize) {
                return prevY + (halfSize - nowSize)/width;
            }
            bool isStart = event & 1;
            // 对现有宽度进行更新
            width += (isStart*2 -1)*L;
            nowSize += curA;
            prevY += dy;
        }
        return 0;
    }
};