#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll q=123456789;
const ll n = 1e18;
ll search(ll n){
if(n == 1) return 1;
if( n > 1) return (search(n-1)%q + search(n-1)%q)%q;
else return 0;
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("count.inp","r",stdin);
    //freopen("count.out","w",stdout);
ll n;
cin>>n;
cout<<search(n)<<endl;
}
