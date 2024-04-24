#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,a[1001],t[1001],r[1001],f[1001];
void readin(){
    fi >> n;
    for (int i=1;i<=n;i++) fi >> t[i];
    for (int i=1;i<=n-1;i++) fi >> r[i];
}
void solve(){
	for (int i=1;i<=n-1;i++){
		a[i] = t[i]+t[i+1]-r[i];
		if (a[i]<0) a[i]=0;
	}
	//for (int i=1;i<=n-1;i++) cout << a[i]<< " ";
	//3 3 5 2
	f[1]=0;
	f[2]=a[1];
	for (int i=3;i<=n;i++){
		if (f[i-2]+a[i-1]>f[i-1]){
			f[i]=f[i-2]+a[i-1];
		}
		else f[i] = f[i-1];
	}
	int m=0;
	for (int i=1;i<=n;i++) m=m+t[i];
	//cout << m;
	m=m-f[n];
	cout << m;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
