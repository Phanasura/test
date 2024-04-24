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
int n,a[1001],dp1[1001],dp2[1001];
void readin(){
	cin >> n;
	for (int i=1;i<=n;i++){
		cin >> a[i];
		dp1[i] = a[i];
		dp2[i] = a[i];
	}
	for (int i=1;i<n;i++){
		for (int j=1;j<i;j++){
			if (a[i] > a[j]){
				dp1[i] = max(dp1[i],dp1[j] + a[i]);
			}
		}
	}
	for (int i=n-1;i>=0;i--){
		for (int j=n;j>1;j--){
			if (a[i] > a[j]){
				dp2[i] = max(dp2[i],dp2[j]+a[i]);
			}
		}
	}
	int res =0;
	for (int i=1;i<=n;i++){
		res = max(res,dp1[i]+dp2[i]-a[i]);
	}
	cout << res;

}


void solve(){
	
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

inp :
6
80 60 30 40 20 10
out:
210
*/
