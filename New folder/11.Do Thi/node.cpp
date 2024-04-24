#include <bits/stdc++.h>
#define INF int64_t(1e9)
#define pii pair<int,int>
#define pll pair<long long, long long>
using namespace std;
const int nmax = 1e5 +5;

void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

struct edge{
    int w, x, y;

};

bool cmp(edge a , edge b){
    return a.w < b.w;
}

int n , m;
vector <edge> ed;
int par[nmax], sizes[nmax];

int get(int a){
    if (a == par[a]) return par[a];
    else return par[a] = get(par[a]);
}

bool joint(int a, int b){
    int u = get(a), v = get(b);
    if (u == v) return false;
    par[u] = v;
    return true;
}

int main(){
    setIO("node");
    cin >> n ;
    for (int i=1;i<=n;i++) par[i] = i, sizes[i] = 1;
    int x;
    while (cin >> x){
        int w,y;
        cin >> y >> w;
        ed.push_back({w,x,y});
    }
    sort(ed.begin(),ed.end(),cmp);
    long long res = 0;
    for (auto x:ed){
        if (joint(x.x, x.y)) res+=x.w;
    }
    cout << res;
return 0;
}
