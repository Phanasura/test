#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
const long long mod = 1e9+7;
long long dp[1005][1001],n,k;
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		//freopen((name + ".out").c_str(), "w", stdout);
	}
}

void readin(){
	cin >> n >> k;
}

void solve(){
	ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	for (int i=0;i<=1000;i++){
		for (int j=0;j<=i;j++){
			if (i==j||j==0) dp[i][j]=1;
			else dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
			dp[i][j] %= mod;
		}
	}
	cout << dp[n][k];
}

int main(){
	//setIO("TEN FILE");
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
