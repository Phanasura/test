#include <bits/stdc++.h>
using namespace std;
int a[1001][1001],n,m
;void readin(){
	cin >> n >> m;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			cin >> a[i][j];
		}
	}
}
void solve(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			sort(a+1,a+n+1);
		}
	}
}
int main(){
	freopen("test.txt","r",stdin);
	readin();
	solve();
	return 0;
}
