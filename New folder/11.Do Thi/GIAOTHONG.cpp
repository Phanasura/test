#include <bits/stdc++.h>
using namespace std;

int n,m,s,t,y,x,w;
const int maxn = 100001;
vector <pair<int,int> > adj[maxn];
int pre[maxn];
const int inf = 1e6;

void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		//freopen((name + ".out").c_str(), "w", stdout);
	}
}

void readin(){
	cin >> n >> m; 
	for (int i=0;i<m;i++){
		cin >> x >> y >> w;  
		adj[x].push_back({y,w});
		adj[y].push_back({x,w});
	}
}

void dijkstra(int s,int t){
	vector<long long> d(n+1,inf);
	vector<bool> visited(n+1,false);
	vector < int > count(n + 1, 0);
	d[s]=0;
	pre[s]=s;
	count[s] = 1;
	priority_queue<pair<int,int> , vector<pair<int,int> > ,greater<pair<int,int> > > q;
	q.push({0,s});
	while (!q.empty()){
		pair<int, int > top= q.top();
        q.pop();
        int kc=top.first;
        int u=top.second;
        if (visited[u]) continue; 
        visited[u]=true;
        for (int a=0;a < adj[u].size();a++){
        	int v = adj[u][a].first;
        	int w = adj[u][a].second;
        	if (d[v] > d[u] + w){
        		d[v] = d[u]+w;
        		q.push({d[v],v});
        		pre[v] = u;  
        		count[v] = count[u];
			}
			else if (d[v] == d[u] + w){
				count[v] += count[u];
			}
		}
	}
	int min_dis = d[n];
    int min_pcnt = count[n];
    cout << min_dis << " " << min_pcnt;
    
}

int main(){
	setIO("GIAOTHONG");
	readin();
    dijkstra(1,n);
	return 0;
}

