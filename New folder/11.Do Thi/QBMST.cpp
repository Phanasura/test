#include<bits/stdc++.h>
using namespace std;
const int MaxN = 1 + 1e5;
typedef long long ll;
int n, m, parent[MaxN];

void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

class Edge {
    public:
        int u, v, w;
        Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {}
        bool operator < (const Edge &op) const {
            return w < op.w;
        }
};
vector<Edge> edges;

void readin(){
	cin >> n >> m;
    for(int i = 0 ; i < m ; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(Edge(u, v, w));
    }
}

int find_set(int u){
    if(u == parent[u]) return u;
    return parent[u] = find_set(parent[u]);
}

void make_set(int u){
    parent[u] = u;
}

void pre_data(){
	for(int i = 1 ; i <= n ; ++i) make_set(i);
    sort(edges.begin(), edges.end());
}

void kruskal(){
	ll ans = 0;
    for(int i = 0 ; i < m ; ++i){
        Edge e = edges[i];
        int u = find_set(e.u);
        int v = find_set(e.v);
        if(u != v){
            ans += e.w;
            parent[u] = v;
        }
    }
    cout << ans;
}

int main(){
	setIO("QBMST");
    readin();
    pre_data();
    kruskal();
    return 0;
}
