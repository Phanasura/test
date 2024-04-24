#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
const int MOD = 123456789;
long long n;
void setIO(string name = "") { 
	ios_base::sync_with_stdio(0);
	cin.tie(0);  
	if (!name.empty()) {
		freopen((name + ".in").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

void readin(){
	cin >> n;
}

void solve(){
	vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[j] = (dp[j] + dp[j - i]) % MOD;
        }
    }
    for (int i=1;i<=n;i++) cout << dp[i] << " ";
}

int main(){
	//setIO("Count");
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
