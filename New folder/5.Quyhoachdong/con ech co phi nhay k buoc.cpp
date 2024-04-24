#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,h[1001],p[1001],nmin,kqmin,k;
void readin(){
	cin >> n >> k;
	for (int i=1;i<=n;i++) cin >> h[i];
}
void solve(){
	p[1]=0;
	for (int i=2;i<=n;i++){
		kqmin=1e5;
		for (int j=1;j<=k;j++){
			if (i-j >= 1){
				kqmin = min(kqmin,p[i-j]+abs(h[i]-h[i-j]));
			}
		}
		p[i]=kqmin;
	}
	cout << p[n];
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
