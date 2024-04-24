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
	int a[n+5],res = 0;
	for (int i=1;i<=n;i++) cin >> a[i];
	int dp[n+5]={0};
	for (int i=1;i<=n;i++){
		dp[i] = 1;
		for (int j=1;j<i;j++){
			if (a[i] >= a[j]){
				dp[i] = max(dp[i],dp[j]+1);
			}
		}
		res = max(res,dp[i]);
	}
	cout << n-res;
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
2 3 5 1 4 7 6
out:
3 (1 chen truoc 2,4 chen truoc 5,6 chen truoc 7) => 3 buoc chen
*/
