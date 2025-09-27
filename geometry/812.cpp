
class Solution {
    public:
        using int2 = pair<int, int>;
        static  int cross(int2& a, int2& b, int2& c) {
            return (b.first - a.first)*(c.second - a.second) - (b.second - a.second)*(c.first - a.first);
        }
        static  double maxArea(vector<int2>& P, int n){
            double maxA=0;
            for(int i=0; i<n-2; i++){
                for(int j=i+1; j<n-1; j++){
                    for(int k=j+1; k<n; k++){
                        double area=abs(cross(P[i],P[j],P[k]));
                        maxA=max(maxA, area);
                    }
                }
            }
            return 0.5*maxA;
        }
        static  double largestTriangleArea(vector<vector<int>>& points) {
            int n = points.size();
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
            return maxArea(hull, k-1);

        }
    };