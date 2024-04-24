#include <bits/stdc++.h>
using namespace std;
#define ll long long
const long long MOD = 123456789;
ll sqr(ll x){
	return x*x;
}
ll res(ll a,ll n){
	if (n==0) return 1; else
	if (n%2==0) return sqr(res(a,n/2))%MOD;
	else return  ( (sqr(res(a,n/2))%MOD)*(a % MOD) ) %MOD;
}
int main() {
    freopen("count.inp","r",stdin);
    freopen("count.out","w",stdout);
    unsigned long long  n;
    cin >> n;
    cout << res(2, n-1) ;
    return 0;
}
    
