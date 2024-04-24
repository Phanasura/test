#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int a[1000],n,dp[10000],res,k;
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++){
		fi >> a[i];
	}
}
void solve(){
	int sum,best;
	for (int i=1;i<=n;i++){
		sum = max(a[i],sum+a[i]);
		best = max(sum,best);
	}
	cout << best;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
inp:
8
5 3 5 7 8 3 6 9
out:

*/
