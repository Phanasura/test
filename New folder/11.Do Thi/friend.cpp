#define fi first
#define se second
#define pb push_back
#define ll long long
#define pii pair<ll, ll>
#define vi vector<int>
#define vii vector<pair<ll, ll>>
#include <bits/stdc++.h>
using namespace std;
const ll mod = 1e9 + 7;
const int lo = 2e9;
const int maxN = 1e6 + 5;
ll n, m, ha, sa, hb, sb;
vii g[maxN];
vi ja, jb, jsa, jsb;
bool p[maxN];
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}
struct comp
{
    bool operator()(pii a, pii b)
    {
        return a.se > b.se;
    }
};
void dijkscon(int s, vi &d){
    d.resize(n + 1);
    priority_queue<pii, vii, comp> pr;
    for (int i = 1; i <= n; i++)
        d[i] = lo;
    memset(p, false, sizeof p);
    d[s] = 0;
    pr.push({s, d[s]});
    while (!pr.empty()){
        pii x = pr.top();
        pr.pop();
        int u = x.fi;
        if (p[u])
            continue;
        p[u] = true;
        for (pii e : g[u]){
            int v = e.fi, w = e.se;
            if (d[u] + w < d[v]){
                d[v] = d[u] + w;
                pr.push({v, d[v]});
            }
        }
    }
}
void res(){
    int kq = lo;
    for (int i = 1; i <= n; i++){
        if (ja[i] + jsa[i] == ja[sa] && jb[i] + jsb[i] == jb[sb] && ja[i] == jb[i])
            kq = min(kq, ja[i]);
    }
    if (kq == lo)
        cout << -1;
    else
        cout << kq;
}
void readin(){
	cin >> n >> m;
    cin >> ha >> sa >> hb >> sb;
    while (m--){
        int x, y, w;
        cin >> x >> y >> w;
        g[x].pb({y, w});
        g[y].pb({x, w});
    }
}

void solve(){
	dijkscon(ha, ja);
    dijkscon(sa, jsa);
    dijkscon(hb, jb);
    dijkscon(sb, jsb);
    res();
}

int main(){
	setIO("friend");
	readin();
	solve();
	return 0;
}
