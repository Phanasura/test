#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
string s1,s2;
int dp[100][100],res,t;
void readin(){
	cin>> s1 >> s2;
	res=0;
}
void solve(){
	for (int i=1;i<=s1.size();i++){
		for (int j=1;j<=s2.size();j++){
			if (s1[i-1]==s2[j-1]) dp[i][j]=dp[i-1][j-1]+1;
			else {
				dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
			}
			res=max(dp[i][j],res);
			//fo << dp[i][j]<< " ";
		}
	    //cout << endl;	
	}
	cout << res<< endl;
	//cout << endl;
}
int main(){
	/*cin >> t;
	while (t--){
		readin();
		solve();
	}*/
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
2
AGGTAB
GXTXAYB
AA
BB
OUT:
4
0*/
