#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
// dp[长度][结束符号][连续长度]
#define int long long
const int mod=20020219;

int dp[20][20][20];
int nums[20];
int len;
int Limits[20];
int dfs(int pos, int num, int cnt, int flag) {
    if (cnt > Limits[num]) return 0;
    if (pos == 0) return 1;
    if (flag && dp[pos][num][cnt] != -1) return dp[pos][num][cnt];

    int numLimit = flag ? 9: nums[pos];
    int ans = 0;
    for (int i = 0; i <= numLimit; i++) {
        if (i == num) ans += dfs(pos-1, num, cnt+1, flag || i < numLimit);
        else ans += dfs(pos-1, i, 1, flag || i < numLimit);
        ans %= mod;
    }
    if (flag) dp[pos][num][cnt] = ans;
    return ans;
}
int sdp[20][10][20][2];
int solve(int pos, int num, int cnt, int flag) {
    // 遍历全部的20位数
    if (cnt > Limits[num]) return 0;
    if (pos == 0) return 1;
    if (flag && dp[pos][num][cnt] != -1) return  dp[pos][num][cnt]; 
    int limit = flag ? nums[pos] : 9;
    int ans = 0;
    for (int i = 0; i < 9; i++) {
        if (i == num) {
            ans += solve(pos, i, cnt+1, flag || i < num);
        } else {
            ans += solve(pos, i, 1, flag || i < num);
        }
    }
    if (flag) dp[pos][num][cnt] = ans;
    return ans;
}

int cul(int x) {
    int pos = 0;
    while(x) {
        nums[++pos] = x%10;
        x /= 10;
    }
    return dfs(pos, 0, 0, 0);
}
signed main()
{
    int t;
    scanf("%lld",&t);
    vector<int>v;
    
    while(t--)
    {
        memset(dp,-1,sizeof(dp));
        memset(nums,0,sizeof(nums));
        memset(Limits,0x3f3f3f3f,sizeof(Limits));
        int l,r,n;
        scanf("%lld%lld%lld",&l,&r,&n);
        while(n--)
        {
            int num,cnt;
            scanf("%lld%lld",&num,&cnt);
            Limits[num]=min(Limits[num],cnt);
        }
        printf("%lld\n",(cul(r)-cul(l-1)+mod)%mod);
    }
}