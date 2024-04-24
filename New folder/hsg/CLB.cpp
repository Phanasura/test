#include <bits/stdc++.h>
using namespace std;
ifstream fi("CLB.INP");
ofstream fo("CLB.OUT");
int n,i,kq,maxx,a[10000],b[10000],kt[10000];
void readin(){
	fi>>n;
    for (i=1; i<=n; i++) {
	    fi>>a[i];
        b[a[i]]++;
    	kt[a[i]]=1;
    	maxx=max(maxx,a[i]);
	}
}
void solve(){
	for (i=1; i<=maxx; i++) {
		if (kt[i]==1) {
			kq=kq+b[i]/i;
		}
	}
}
int main () {
    readin();
    solve();
    fo << kq;
    return 0;
    fi.close();
    fo.close();
}
    
