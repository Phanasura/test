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

void readin(){
	
}
const long long mod = 1e9+7;
void solve(){
	int n,k;
	cin >> n >> k;
	long long res = 1;
	if (k>n) res = 0;
	for (int i=n-k+1 ; i<=n ; i++){
		res = (res*i)%mod;
	}
	cout << res ;
}

int main(){
	//setIO("TEN FILE");
	//readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
