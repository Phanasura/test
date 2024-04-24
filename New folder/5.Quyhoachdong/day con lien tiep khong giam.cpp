#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,res=0,dp[1001],a[1001];
void readin(){
	cin >> n;
	for (int i=1;i<=n;i++){
		cin >> a[i];
	}
}
void solve(){
	for (int i=1;i<=n;i++){
		dp[i]=1;
		for (int j=i-1;j<i;j++){
			if (a[i]>=a[j]) dp[i]=max(dp[i],dp[j]+1);
			res=max(res,dp[i]);
			cout << dp[i] << " ";
		}
	}
	cout << endl << res;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
/*
#include <iostream>
using namespace std;
 
int main() {
    freopen("DAYKT.INP","r",stdin);
    freopen("DAYKT.OUT","w",stdout);
    int n, a[1000], b[1000];
    cin >> n;
    for(int i=0; i < n; i++) {
        cin >> a[i];
        b[i] = 1;
    }
    for(int i=n-1; i>0; i--) {
        if(a[i] >= a[i-1]) {
            b[i-1] += b[i];
        }
    }
    int m = b[0];
    for (int i=1; i<n; i++) {
        if(m < b[i]) m = b[i];
    }
    cout << m << endl;
    int vt = 0;
    for (int i = 0; i < n; i++) {
        if(b[i] == m) vt = i;
    }
    for (int i = vt; i < vt + m; i++) {
        cout << a[i] << " ";
    }
    return 0;
}*/
