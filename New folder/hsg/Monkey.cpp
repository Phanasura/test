#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
int n, a[MAXN][MAXN], dp[MAXN][MAXN];
void setIO(string name = "") { 
	ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

void readin(){
	cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = n+1; i <= 2*n-1; i++) {
        for (int j = 1; j <= 2*n-i; j++) {
            cin >> a[i][j];
        }
    }
}

void solve(){
	for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = a[i][j] + max(dp[i-1][j-1], dp[i-1][j]);
        }
    }
    for (int i = n+1; i <= 2*n-1; i++) {
        for (int j = 1; j <= 2*n-i; j++) {
            dp[i][j] = a[i][j] + max(dp[i-1][j], dp[i-1][j+1]);
        }
    }
    cout << dp[2*n-1][1] << endl;
}

int main(){
	setIO("MONKEY");
	readin();
	solve();
	return 0;
}
