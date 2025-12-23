class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        vector<int> points;
        for (int i = 0; i < events.size(); i++) {
            points.push_back(events[i][0]-1);
            points.push_back(events[i][1]);
        }
        sort(points.begin(), points.end());          // ✅ 先排序
        int len = std::unique(points.begin(), points.end()) - points.begin();  // step 3
        for (int i = 0; i < events.size(); ++i)  {
            events[i][0] = lower_bound(points.begin(), points.begin() + len, events[i][0]-1) - points.begin();
            events[i][1] = lower_bound(points.begin(), points.begin() + len, events[i][1]) - points.begin();
        }                            // step 4
        sort(events.begin(), events.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1];
        });
        int n = points.size();
        vector<int>dp(points.size(), 0);
        for (int i = 0; i < events.size(); i++) {
            int start = events[i][0];
            int end = events[i][1];
            dp[end] = max(dp[end], events[i][2]);
        }
        // int maxV = 0;
        for (int i = 1; i < n; i++) {
            dp[i] = max(dp[i], dp[i-1]);
        }
        int ans = 0;
        for (int i = 0; i < events.size(); i++) {
            int start = events[i][0];
            int end = events[i][1];
            ans = max(ans, dp[start] + events[i][2]);
        }
        return ans;
    }
};