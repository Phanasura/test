#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,ptc,vtx,a[1001];
void readin(){
	fi >> n >> vtx ;
	for (int i=1;i<=n;i++) fi >> a[i];
}

void solve(){
	n=n-1;
    for (int i=vtx;i<n;i++){
    	a[i]=a[i+1];
	}
	for (int i=1;i<n;i++) cout << a[i] << " ";
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
