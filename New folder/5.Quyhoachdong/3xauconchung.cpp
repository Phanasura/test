#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
string s1,s2,s3;
int dp[100][100][100],t,n,m,l;
void readin(){
	cin >> n >> m >> l >> s1 >> s2 >> s3;
	memset(dp,0,sizeof(dp));
}

void solve(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			for (int k=1;k<=l;k++){
				if (s1[i-1] == s2[j-1] && s2[j-1] ==  s3[k-1])
				    dp[i][j][k] = 1+ dp[i-1][j-1][k-1];
				else 
				    dp[i][j][k] = max(dp[i-1][j][k],max(dp[i][j-1][k],dp[i][j][k-1]));
		    }
		}
	}
	
	cout << dp[n][m][l] << endl;
}

int main(){
	/*fi >> t;
	while(t--){
		readin();
	    solve();
	}*/
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*inp:
5 8 13
geeks geeksfor geeksforgeeks
out:
5*/
