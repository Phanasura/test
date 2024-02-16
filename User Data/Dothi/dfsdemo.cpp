#include <bits/stdc++.h>
#define file "dfsdemo"
#define ll long long
#define ld long double
#define ull unsigned long long
#define pii pair<ll, ll>
#define fi first
#define se second
#define maxn 100001
using namespace std;
ll maxx = -1e18, minn = 1e18;
ll n,m;
bool visited[maxn];
vector<ll> a[maxn];
void dfs(ll u){
    visited[u]=true;
    cout<<u<<"\n";
    for(int i:a[u]){
        if(!visited[i]){
            dfs(i);
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen(file ".inp", "r", stdin);
    freopen(file ".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>m;
    while(m--){
        ll x,y;
        cin>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for(int i=1;i<=n;i++){
        sort(a[i].begin(),a[i].end());
    }
    for(int i=1;i<=n;i++){
        if(!visited[i]){
            dfs(i);
        }
    }

}

