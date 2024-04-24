#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll l,r,n,m,i,d[1000001],x,y,c,tr[1000001];
vector <pair <ll,ll>> a[1000001];
void bfs (ll k)
{
    priority_queue <pair <ll,ll> ,vector <pair <ll,ll>>, greater <>> q;
    q.push({k,0});
    while (! q.empty())
    {
        pair <ll,ll> top=q.top();
        ll fi=top.first,sc=top.second;
        q.pop();
        if (d[fi] != sc) continue;
        for (auto j: a[fi])
        {
            ll v=j.first,w=j.second ;
            if (d[v]> d[fi]+w)
            {
                d[v]=d[fi]+w;
                tr[v]=fi;
                q.push({v,d[v]});
            }
        }
    }
}
int main()
{
    freopen("DijkstraHeap.inp","r",stdin);
    freopen("DijkstraHeap.out","w",stdout);
    cin>>n>>m;
    for (i=1;i<=m;i++)
    {
        cin>>x>>y>>c;
        a[x].push_back({y,c});
        a[y].push_back({x,c});
    }
    for (i=1;i<=n;i++) d[i]=1e18;
    d[1]=0;
    bfs(1);
    cout<<d[n]<<endl;
    ll h=n;
    vector <ll> lu;
    while (h!=1)
    {
        lu.push_back(h);
        h=tr[h];
    }
    cout<<1<<" ";
    for (ll j=lu.size()-1;j>=0;j--)
    {
        cout<<lu[j]<<" ";
    }
    return 0;
}
