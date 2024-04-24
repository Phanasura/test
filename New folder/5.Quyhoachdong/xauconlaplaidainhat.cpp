#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int a[1000][1001],n,m,dp[1000][1001],res;
string s;
void readin(){
    fi >> n;
    fi >> s;
}
void solve(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			if (s[i-1]==s[j-1] && i!=j) dp[i][j]=dp[i-1][j-1]+1;
			else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
			//res=max(res,dp[i][j]); 
		}
	}
    cout  << dp[n][n];
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
5
accct
out :
2
*/
