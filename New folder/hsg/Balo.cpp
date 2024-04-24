#include <bits/stdc++.h>
using namespace std;

//const int mn = 20;
const int mm = 1e8;

int n, m;
int w[21], v[21];
int dp[mm];
ifstream fi("Balo.Inp");
ofstream fo("Balo.Out");
void readin(){
	fi >> n >> m;
    for (int i = 0; i < n; i++) {
        fi >> w[i] >> v[i];
    }
}
void solve(){
	for (int j = 0; j <= m; j++) {
        dp[j] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = m; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    fo << dp[m] << endl;
}
int main() {
	readin();
	solve();
    return 0;
    fi.close();
    fo.close();
}
