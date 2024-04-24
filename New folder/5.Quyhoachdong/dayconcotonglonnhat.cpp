#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,res=0,dp[1001],a[1001];
void readin(){
	cin >> n;
	for (int i=1;i<=n;i++){
		cin >> a[i];
	}
}
void solve(){
	for (int i=1;i<=n;i++){
		dp[i]=a[i];
		for (int j=1;j<i;j++){
			if (a[i]>=a[j]) dp[i]=max(dp[i],dp[j]+a[i]);
			res=max(res,dp[i]);
			//cout << dp[i] << " ";
		}
	}
	cout << endl << res;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
/*inp:
7
1 101 2 3 100 4 5
out:
106 (giai thich 106 = 1+2+3+100)
*/
