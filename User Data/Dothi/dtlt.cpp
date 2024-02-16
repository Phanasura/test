#include <bits/stdc++.h>
#define INF int64_t(1e9)
#define pll pair <long long, long long>
#define file "dtlt"
using namespace std;
const int nmax= 20005;
int n, m;
vector <int> adj[nmax];
vector <vector<int>> res;
vector <int> cur;
bool vis[nmax];
void dfs(int u)
{
    cur.push_back(u);
    vis[u]=true;
    for (auto v:adj[u])
    {
        if (!vis[v]) dfs(v);
    }
}
int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    freopen(file".inp","r",stdin);
    freopen(file".out","w",stdout);
    cin >> n >> m;
    for (int i=1;i<=m;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);

    }
    for (int i=1;i<=n;i++) sort(adj[i].begin(), adj[i].end());
    memset(vis,0,sizeof vis);
    for (int i=1;i<=n;i++)
    {
        if (!vis[i]) cur.clear(), dfs(i), res.push_back(cur);
    }
    cout << res.size() << "\n";
    for (int i=0;i<res.size();i++)
    {
        cout << res[i].size() << " ";
        //sort(res[i].begin(), res[i].end());
        for (auto x:res[i]) cout << x << " ";
        cout << "\n";
    }
return 0;
}
