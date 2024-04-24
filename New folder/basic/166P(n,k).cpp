#include <bits/stdc++.h>
using namespace std;

const long long mod=1e9+7;

int n,k,t;
void readin(){
	cin >> n >> k;
}

void solve(){
	long long res=1;
	if (k>n) res=0;
	for (int i=n-k+1;i<=n;i++){
		res = (res*i)%mod;
	}
	cout << res<< endl;
}

int main(){
	cin >> t ;
	while (t--){
		readin();
	    solve();
	}
	return 0;
}
