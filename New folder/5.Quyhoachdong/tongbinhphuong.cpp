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
	cin >>n;
}

void solve(){
	long long dp[n+5];
	for (int i=0;i<=n;i++){
		dp[i]= i;
	}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=sqrt(i);j++){
			dp[i] = min(dp[i],dp[i-j*j]+1);
		}
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
100
out :1
giai thich 100 = 5^2 + 5^2 +5^2 + 5^2
=> co duy nhat 1 so 5*/
