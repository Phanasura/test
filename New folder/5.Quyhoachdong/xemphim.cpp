#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inP").c_str(), "r", stdin); 
		//freopen((name + ".out").c_str(), "w", stdout);
	}
}
int W,n;
void readin(){
	cin >> W >> n;
}

void solve(){
	int a[n+5];
	int dp[101][2501];
	for (int i=1;i<=n;i++){
		cin >> a[i];
	}
	memset(dp,0,sizeof(dp));
	for (int i=1;i<=n;i++){
		for (int j=1;j<=W;j++){
			if (j >= a[i]){
				dp[i][j] = max(dp[i-1][j],dp[i-1][j-a[i]]+a[i]);
			}
			else dp[i][j] = dp[i-1][j];
		}
	}
	cout << dp[n][W];
}

int main(){
	//setIO("TEN FILE");
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
	
}
/*inp:
259 5
81 
58
42
33
61
out:
242
*/
