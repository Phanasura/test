#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int a[1000][1001],n,m,dp[1000][1001],res;
void readin(){
	cin >> n >> m;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			cin >> a[i][j];
			dp[i][j]=a[i][j];
		}
	}
}
void solve(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			if (a[i][j]==0) continue;
			if (a[i][j]==a[i-1][j] && a[i][j]==a[i][j-1] && a[i][j]==a[i-1][j-1]){
				dp[i][j]=min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
			}
			res=max(res,dp[i][j]);
		}
	}
	cout << res<< endl;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){ 
		    cout << dp[i][j] << " ";
		}
		cout << endl;
	}
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
6 5
0 1 1 0 1
1 1 0 1 0
0 1 1 1 0
1 1 1 1 0
1 1 1 1 1
0 0 0 0 0
2 2 
0 0 
0 0
out :
3
0
*/
