#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inP").c_str(), "r", stdin); 
		//freopen((name + ".out").c_str(), "w", stdout);
	}
}
int n;
string s;
void readin(){
	cin >> n >> s;
}

void solve(){
	int dp[n+5][n+5];
	memset(dp,0,sizeof(dp));
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			if (s[i-1] == s[j-1] && i!=j) dp[i][j] = dp[i-1][j-1]+1;
			else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
		}
	}
	cout << dp[n][n];
}

int main(){
	//setIO("TEN FILE");
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
3
abc 
out:0
inp:
5
axxxy
out: 2*/
