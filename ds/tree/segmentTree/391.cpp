class Solution {
    public:
        // const int Num = 20010;
        #define N 100000
        long long x[N];
        struct query {
            long long l, r;
            long long h;
            int add;
        }q[N];
        static bool cmp(query &x, query &y) {
            if (x.h != y.h) return x.h < y.h;
            return x.add < y.add;
        }
        struct node {
            long long l, r;
            int lazy;
            long long sum;
            int son;
        }Nodes[N];

        void build(int l, int r, int idx) {
            Nodes[idx].l = l;
            Nodes[idx].son = 0;
            Nodes[idx].r = r;
            Nodes[idx].lazy = Nodes[idx].sum = 0;
            if (l == r) return;
            int mid = l + ((r - l)>>1);
            build(l, mid, idx*2);
            build(mid+1, r, idx*2+1);
        }

        void pushup(int idx) {
            if (Nodes[idx].lazy) {
                Nodes[idx].sum = x[Nodes[idx].r + 1] - x[Nodes[idx].l];
            }  else if (Nodes[idx].l == Nodes[idx].r) return;
            else {
                Nodes[idx].sum = Nodes[idx*2].sum + Nodes[idx*2+1].sum;
            }
        }
        bool update(int l, int r, int adder, int idx, int sum) { 
            if (l <= Nodes[idx].l && Nodes[idx].r <= r) {
                if (sum >= 1 && adder >= 1) return false;
                if (Nodes[idx].lazy >= 1&& adder >=1) {
                    return false;
                }
                Nodes[idx].lazy += adder;

                if (Nodes[idx].lazy && Nodes[idx].son) return false;
                pushup(idx);
                return true;
            }
            bool res = true;
            int mid = Nodes[idx].l + ((Nodes[idx].r - Nodes[idx].l)>>1);
            if (l <= mid)  res &= update(l, r, adder, idx*2, sum + Nodes[idx].lazy);
            if (r > mid) res &= update(l, r, adder, idx*2+1, sum + Nodes[idx].lazy);
            Nodes[idx].son =  Nodes[idx*2].lazy + Nodes[idx*2+1].lazy + Nodes[idx*2].son + Nodes[idx*2+1].son;
            pushup(idx);
            return res;
        }

        bool isRectangleCover(vector<vector<int>>& rectangles) {
            int n = rectangles.size();
            int minX =200000;
            int maxX = -1;
            int minY = 200000;
            int maxY = -1;
            long long total_size = 0;
            for (int i = 0; i < n; i++) {
                x[i*2] = rectangles[i][0];
                x[i*2+1] = rectangles[i][2];
                q[i*2] = query{rectangles[i][0], rectangles[i][2], rectangles[i][1], 1};
                q[i*2+1] = query{rectangles[i][0], rectangles[i][2], rectangles[i][3], -1};
                total_size += (long long)(rectangles[i][2] - rectangles[i][0])*(long long)(rectangles[i][3] - rectangles[i][1]);
                minX = min(minX, rectangles[i][0]);
                maxX = max(maxX, rectangles[i][2]);
                minY = min(minY, rectangles[i][1]);
                maxY = max(maxY, rectangles[i][3]);
            }
            sort(x, x+n*2);
            sort(q, q+n*2, cmp);
            int k = unique(x, x+n*2) - x;
            build(0, k, 1);
            long long size = 0;
            for (int i = 0; i < n*2-1; i++) {
                int l = lower_bound(x, x+k, q[i].l) - x;
                int r = lower_bound(x, x+k, q[i].r) - x-1;
                if (!update(l, r, q[i].add,1, 0)) {
                    printf("erer\n");
                    return false;
                }
                size +=(long long)(Nodes[1].sum) * (long long)(q[i+1].h - q[i].h);
            }
            return size == (long long)(maxX - minX) * (long long)(maxY - minY) && size == total_size;
        }
    };