#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int a[1000][1001],n,m,dp[1000][1001],res;
void readin(){
	fi >> n >>m;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			fi >> a[i][j];
			dp[i][j]=a[i][j];
		}
	}
}
void solve(){
    for (int i=1;i<=n;i++){
    	for (int j=1;j<=m;j++){
    		if (i==1&&j==1) dp[i][j]=dp[i][j];
    		else {
    			if (j==1) dp[i][j]=dp[i][j]+dp[i-1][j];
    			else {
    				if (i==1) dp[i][j]=dp[i][j]+dp[i][j-1];
    				else {
    					dp[i][j]= dp[i][j]+min(dp[i][j-1],min(dp[i-1][j],dp[i-1][j-1]));
    		           // res=max(res,dp[i][j]);
					}
				}
			}
			
		}
	}
	fo << dp[n][m];
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
3 3
1 2 3
4 8 2
1 5 3
out :
8
*/
