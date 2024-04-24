#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int n,a[1001],dp[1000],s,t;
void readin(){
	cin >> n >> s;
	for (int i=0;i<n;i++) cin >> a[i];
}
void solve(){
	dp[0]=1;
	memset(dp,0,sizeof(dp));
	for (int i=0;i<n;i++){
    	for (int j=s;j>=a[i];j--){
    		if (dp[j-a[i]]==1) dp[j]=1;
		}
	}
	for (int i=0;i<=n;i++){
		cout << dp[i] << " ";
	}
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
