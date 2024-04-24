#include <bits/stdc++.h>
using namespace std;
long long n, t=0;

void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

struct Edge	{
    long long from, to, weight;
    Edge(long long _from, long long _to, long long _weight) : from(_from), to(_to), weight(_weight) {}
};

struct DSU{
    vector<long long> par, size;
    DSU(long long n)
    {
        par.resize(n);
        size.resize(n);
        for (long long i = 0; i < n; i++)
        {
            par[i] = i;
            size[i] = 1;
        }
    }
    long long find(long long x){
        if (par[x] != x){
            par[x] = find(par[x]);
        }
        return par[x];
    }
    void unite(long long x, long long y){
        long long rootX = find(x);
        long long rootY = find(y);
        if (rootX != rootY){
            if (size[rootX] < size[rootY]){
                swap(rootX, rootY);
            }
            par[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
};
long long Krus(long long n, vector<Edge> &edges){
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
         { return a.weight < b.weight; });
    DSU dsu(n);
    for (const Edge &e : edges){
        if (dsu.find(e.from) != dsu.find(e.to)){
            dsu.unite(e.from, e.to);
            t += e.weight;
        }
    }
    return t;
}

int main(){
	setIO("MSTKR");
    cin >> n;
    vector<Edge> e;
    for (long long i = 0; i < n; i++){
        for (long long j = 0; j < n; j++){
            long long weight;
            cin >> weight;
            if (weight != 0 && j > i){
                e.push_back(Edge(i, j, weight));
            }
        }
    }
    long long res = Krus(n, e);
    cout << res;
    return 0;
}
