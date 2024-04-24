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
int n,m;
string s2,s1;
void readin(){
	cin >> s1 >> s2;
	n = s1.length();
	m = s2.length();
}

void solve(){
	int dp[n+2][m+2];
	for (int i=0;i<= n;i++){
		for (int j=0;j<=m;j++){
			if (i==0 || j==0){
				dp[i][j] = i+j;
			}
			else if (s1[i-1] == s2[j-1]){
				dp[i][j] = dp[i-1][j-1];
			}
			else{
				dp[i][j] = min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
				
			}
		}
	}
	cout << dp[n][n];
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
geeks gesks
out 
1*/ 
