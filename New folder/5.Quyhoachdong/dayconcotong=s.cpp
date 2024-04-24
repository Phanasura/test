#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inP").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

/*void readin(){
	cin >> n >> s;
	for (int i=1)
}*/

void solve(){
	int n,s,dp[1001],a;
	cin >> n >> s;
	dp[0]=1;
	for (int i=1;i<=n;i++){
		cin >> a;
		dp[a]=1;
		for (int j=s;j>=a;j--){
			if (dp[j-a]==1) dp[j]=1;
		}
	}
	if (dp[s]==1) cout <<"yes";
	else cout << "no";
}

int main(){
	//setIO("TEN FILE");
	//readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
inp:
5 6
1 2 4 3 5
out : yes*/
