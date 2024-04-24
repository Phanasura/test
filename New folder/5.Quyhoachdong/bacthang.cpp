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
int n,k;
const long long mod = 1e9+7;
void readin(){
	cin >> n >> k;
}

void solve(){
	long long dp[n+5]={0};
	dp[0]=dp[1]=1;
	for (int i=2;i<=n;i++){
		for (int j=1;j<=min(i,k);j++){
			dp[i] +=dp[i-j];
			dp[i]%=mod;
		}
	}
	cout << dp[n];
}

int main(){
	//setIO("TEN FILE");
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}/*
inp:
2 2
out:
2
inp:
4 2
out:
5*/
