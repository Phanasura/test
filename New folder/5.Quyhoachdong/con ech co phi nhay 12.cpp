#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,h[1001],p[1001],nmin;
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++) fi >> h[i];
}
void solve(){
	p[1]=0;
	p[2]=abs(h[2]-h[1]);
	for (int i=3;i<=n;i++){
		p[i]=min((p[i-1]+abs(h[i]-h[i-1])),(p[i-2]+abs(h[i]-h[i-2])));
	}
	cout << p[n];
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
