#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,k,a[1001],t[1001];
void readin(){
	cin >> n >> k;
	for (int i=1;i<=n;i++) cin >> a[i];
	t[0]=0;
	for (int i=1;i<=n;i++) {
		t[i] = t[i-1]+a[i];
	}
}

void solve(){
	int max=0,d,c;
	for (int l=1;l<=n;l++){
		for (int r=l;r<=n;r++){
			if (((t[r]-t[l-1] )% k==0) && ((r-l)+1>max)){
				max= (r-l)+1; 
				d=l; 
				c=r;
			}
		}
	}
	cout << "day {";
	for (int i=d;i<=c;i++) cout << a[i] << " ";
	cout << "}="<<t[c]-t[d-1] << " mod k = "<<(t[c]-t[d-1])%k; 
}
int main(){
	readin();
	solve();
	//for (int i=1;i<=n;i++) cout << t[i] << " ";
	return 0;
	fi.close();
}
/*
int main(){
	int n,k,a,dp[1001][1001];
	cin >> n >> k;
	dp[0][0]=0;
	for (int i=1;i<k;i++) dp[0][i]=1005;
	for (int i=1;i<=n;i++){
		cin >> a;
		a%=k;
		for (int j=0;j<k;j++){
			dp[i][j] = max(dp[i-1][j],dp[i-1][(j+k-a)%k]+1);
		}
	}
	cout << dp[n][0];
}*/



/*
inp:
10 3
2 3 5 7 9 6 12 7 11 15
out:
9
*/
