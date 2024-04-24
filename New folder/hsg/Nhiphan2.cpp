#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
long long n,a[10000],kt,dem;
void readin(){
	fi >> n;
}
void xuly(){
	kt=1;
	for (int i=1;i<=n;i++){
	    if (a[i]==1&&a[i+1]==1) kt=0;	
	}
	if (kt==1) dem=dem+1;
}
void bt(int i){
	for (int j=0;j<=1;j++){
		a[i]=j;
		if (i==n) xuly();
		else bt(i+1);
	}
}
void solve(){
	bt(1);
	fo << dem;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
