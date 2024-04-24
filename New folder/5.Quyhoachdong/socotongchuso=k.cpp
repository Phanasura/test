#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int n,k,dp[1000][50001],res;
const long long mod=1e9+7;
void readin(){
	cin >> n >>k;
}
void solve(){
	for (int i=0;i<101;i++) dp[i][0]=0;
	for (int i=0;i<50000;i++) dp[0][i]=0;
	for (int i=1;i<=9;i++) dp[1][i]=1;
	for (int i=1;i<=100;i++){
		for (int so=0;so<=9;so++)
		for (int j=so;j<=50000;j++){
			dp[i][j]=(dp[i][j]%mod+dp[i-1][j-so]%mod)%mod;
		}
	}
	cout << dp[n][k];
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
2
2 2
4 2
out :
2
5
*/
