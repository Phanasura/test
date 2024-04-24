#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int a[1000][1001],n,m,dp[1000],res;
void readin(){
	fi >> n;
}
void solve(){
    dp[1]=1; dp[2]=2; dp[3]=4;
    for (int i=4;i<100;i++){
    	dp[i]=dp[i-3]+dp[i-2]+dp[i-1];
	}
	fo << dp[n];
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
out :
13
*/
