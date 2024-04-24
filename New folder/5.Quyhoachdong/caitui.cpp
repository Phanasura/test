#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("Balo.inp");

long long dp[10000][10000],n,m,i,j,res=0;

struct data
{
	long long w=0,v=0;
};
data a[10000];

void nhap(){
    fi >> n >> m;
    for (long long i=1;i<=n;i++){
    	fi >> a[i].w>>a[i].v;
	}
}
void solve(){
	for (long long i=1;i<=n;i++){
		for (long long j=1;j<=m;j++){
			if (j<a[i].w) dp[i][j]=dp[i-1][j];
			else {
				dp[i][j]=max(dp[i-1][j],dp[i-1][j-a[i].w]+a[i].v);
			}
		//	res = max(res,dp[i][j]);
		}
	}
	cout << dp[n][m];
	/*for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
		    cout << dp[i][j]<<" ";
		}
		cout << endl;
	}*/
	
}
int main(){
    nhap();	
	solve();
	return 0;
	fi.close();
	fo.close();
}
