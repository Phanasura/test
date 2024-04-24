#include <bits/stdc++.h>
using namespace std;

ifstream fi("test.txt");
ofstream fo("kq.txt");
int n,m,w[100],v[100],dp[100][100],vt[100];
void readin(){
	fi >> n >> m;
	for (int i=1;i<=n;i++){
		fi >> w[i] >> v[i];
	}
}

void tb(){
	int t=1;
	while (n>0){
		if (dp[n][m]==dp[n-1][m]) --n;
		else{
			vt[t]=n; t++;
			m=m-v[n];
			--n;
		}
	}
	for (int i=t-1;i>0;i--) fo << vt[i] << " ";
}

void solve(){
	for (int i=1;i<=n;i++)
	    for (int j=0;j<=m;j++){
	    	dp[i][j] = dp[i-1][j];
	    	if (j>=w[i])
	    	    dp[i][j]=max(dp[i][j],dp[i-1][j-w[i]]+v[i]);
		}
	fo << dp[n][m]<< endl;
	tb();
}

int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
