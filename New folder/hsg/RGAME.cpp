#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;
int a[MAXN];
double dp[MAXN][3];
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        dp[0][0] = 0;
        dp[1][0] = 0;
        dp[1][1] = a[1];
        dp[2][0] = 0;
        dp[2][1] = a[2];
        dp[2][2] = a[1] + a[2] * 0.5;
        for (int i = 3; i <= n; i++) {
            dp[i][0] = dp[i-1][0];
            dp[i][1] = max(dp[i-2][0] + a[i-1], dp[i-1][1] + a[i]);
            dp[i][2] = max(dp[i-3][0] + a[i-2] + a[i-1] * 0.5, max(dp[i-2][1] + a[i-1] * 0.5 + a[i], dp[i-1][2]));
        }
        cout << dp[n][1];
    }
    return 0;\
    
}
