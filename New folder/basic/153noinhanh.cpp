#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,a[1001],pre[1001];
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++){
		fi >> a[i];
	}
}
void xuat(){
	for (int i=1;i<=n;i++)
	cout << pre[i]<< " ";
}
void solve(){
	pre[0]=0;
	for (int i=1;i<=n;i++){
		pre[i]=pre[i-1]+a[i];
	}
	xuat();
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
