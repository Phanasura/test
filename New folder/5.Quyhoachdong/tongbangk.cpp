#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int a[1000][1001],n,k,dp[1000][1001],res;
const long long mod=1e9+7;
void readin(){
	cin >> n >>k;
}
void solve(){
	int a[n+5];
	long long dp[k+5] = {0};
	dp[0] = 1;
	for (int i=0;i<n;i++){
		cin >> a[i];
	}
	for (int i=1;i<=k;i++){
		for (int j=0;j<n;j++){
			if (i >= a[j]){
				dp[i] = (dp[i]+dp[i-a[j]])%mod;
			}
		}
	}
	cout << dp[k];
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
inp:
3 7
1 5 6
out :
6
*/
