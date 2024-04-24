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
string s;
void readin(){
	cin  >> s;
}

void solve(){
	if (s[0] == '0'){
		cout << 0 << endl;
		//continue;
	}
	int n=s.size();
	int dp[n+1];
	dp[0] = 1;
	dp[1] = 1;
	for (int i=2;i<=n;i++){
		dp[i]  = 0 ;
		if (s[i-1] > '0'){
			dp[i] = dp[i-1];
		}
		if (s[i-2] == '1' || (s[i-2] == '2' && s[i-1] < '7')){
			dp[i] +=dp[i-2];
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
123
out: 3
inp: 2563
out:2
*/
