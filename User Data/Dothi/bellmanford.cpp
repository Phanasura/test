#include <bits/stdc++.h>
#define ll long long
#define file "bellmanford"
using namespace std;
const int N = 1001;
const int maxD = 1e9;
struct T
{
    ll x, y, v;
};
ll dem = 0, n, m, s, t, d[N], tr[N];
T a[N];
void bellman()
{
    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (d[a[j].x] < maxD && d[a[j].y] > d[a[j].x] + a[j].v)
            {
                d[a[j].y] = d[a[j].x] + a[j].v;
                tr[a[j].y] = a[j].x;
            }
        }
    }
}
int main()
{
    freopen(file ".inp", "r", stdin);
    freopen(file ".out", "w", stdout);
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++)
    {
        cin >> a[i].x >> a[i].y >> a[i].v;
        d[i] = maxD;
    }
    d[s] = 0;
    bellman();
    cout << d[t] << endl;
    while (t != s)
    {
        cout << t << "<-";
        t = tr[t];
    }
    cout << s;
}