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
int n;
void readin(){
	cin >> n;
}

void solve(){
	int a[n+5],dp[n+5]={0};
	for (int i=1;i<=n;i++){
		cin >> a[i];
	}
	dp[1] = a[1];
	dp[2] = max(a[1],a[2]);
	for (int i=3;i<=n;i++){
		dp[i] = max(dp[i-2]+a[i],dp[i-1]);
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
inp:
7
6 7 1 3 8 2 4
out :
19
giai thich 19 = 6+1+8+4;
*/
