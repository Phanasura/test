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
int n,ins,cop,re;
void readin(){
	cin >> n >> ins >> re >> cop;
}

void solve(){
	int dp[n+5] = {0};
	dp[0] = 0;
	dp[1] = ins;
	for (int i=2;i<=n;i++){
		if (i&1) dp[i]=min(dp[i-1]+ins,dp[(i+1)/2]+cop+re);
		else dp[i] = min(dp[i-1]+ins,dp[i/2]+cop);
	}
	cout << dp[n];
}

int main(){
	//setIO("TEN FILE");
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
9
1 2 1
out :
5
(i,i,c,c,i)
*/
