#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll nmax = 1e5+5;
ll n,m, c[nmax];

void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

struct Edge{
    ll u,v,w;
} e[nmax];

struct DSU{
    ll par[nmax];
    void init(ll n){
        for(int i =1; i<=n; i++) par[i] = i;
    }
    ll find(ll u){
        if (par[u] == u) return u;
        return par[u] = find(par[u]);
    }
    bool join(ll u, ll v){
        u = find(u); v = find(v);
        if (u == v) return false;
        par[v] = u;
        return true;
    }
} dsu;

bool cmp(Edge a, Edge b){
    return a.w>b.w;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    setIO("attack");
    cin>>n>>m;
    dsu.init(n);
    ll sum = 0;
    for(int i = 1; i<=n; i++) cin>>c[i];
    for(int i = 1; i<=m; i++){
        ll x,y;
        cin>>x>>y;
        e[i] = {y,x,c[x]+c[y]};
        sum+=c[x]+c[y];
    }
    sort(e+1,e+m+1,cmp);
    ll ans = 0;
    for(int i = 1; i<=m; i++){
        if (!dsu.join(e[i].u, e[i].v)) continue;
        ans+=e[i].w;
    }
    cout<<sum-ans;
    return 0;
}
