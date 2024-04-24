#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
struct dta{
	int x,y;
};
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inP").c_str(), "r", stdin); 
		//freopen((name + ".out").c_str(), "w", stdout);
	}
}

bool cmp(dta a,dta b){
	return a.x < b.x;
}
int n;
dta a[1000+5];
int dp[1000+5];
void readin(){
	cin >> n;
	for (int i=1;i<=n;i++){
		cin >> a[i].x >> a[i].y;
		dp[i]=1;
	}
}

void solve(){
	
	sort(a+1,a+n+1,cmp);
	for (int i=1;i<=n;i++){
		for (int j=1;j<i;j++){
			if (a[i].x>a[j].y) dp[i] = max(dp[i],dp[j]+1);
		}
	}
	cout << dp[n];
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
inp:/
5
5 24 39 60 15 28 27 40 50 90
out:
3*/
