#include <bits/stdc++.h>

using namespace std;

ifstream fi("chungcake.inp");
ofstream fo("chungcake.out");

long long n,a[1000000],v,t=0,res,s;

void nhap(){
	fi>>n>>v;
	for (long long i=1;i<=n;i++) fi>>a[i];
}

void backtracking(long long res,long long s) {
    t=max(t,s);
    for (long long i=res+1;s+a[i]<=v&&i<=n;i++){
    	backtracking(i,s+a[i]);
    }
}
        
void solve(){
	sort(a+1,a+n+1);
    backtracking(0,0);
    fo<<t;
}

int main(){
	nhap();
	solve();
	return 0;
	fi.close();
	fo.close();
}
