#include <bits/stdc++.h>
using namespace std;
//ifstream fi("test.txt");
//ofstream fo("kq.txt"); 
int n,m,s,t,y,x,w;
const int maxn = 100001;
vector <pair<int,int> > adj[maxn];
int pre[maxn];
const int inf = 1e5;
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}
void readin(){
	cin >> n >> m >> s >> t; 
	for (int i=0;i<m;i++){
		cin >> x >> y >> w;  
		adj[x].push_back({y,w});
		adj[y].push_back({x,w});
	}
}
void dijkstra(int s,int t){
	vector<long long> d(n+1,inf);
	vector<bool> visited(n+1,false);
	d[s]=0;
	pre[s]=s;
	priority_queue<pair<int,int> , vector<pair<int,int> > ,greater<pair<int,int> > > q;
	q.push({0,s});
	while (!q.empty()){
		pair<int, int > top= q.top();
        q.pop();
        int kc=top.first;
        int u=top.second;
        if (visited[u]) continue; 
        visited[u]=true;
        //if (kc > d[u]) continue;
        for (int a=0;a < adj[u].size();a++){
        	int v = adj[u][a].first;
        	int w = adj[u][a].second;
        	if (d[v] > d[u] + w){
        		d[v] = d[u]+w;
        		q.push({d[v],v});
        		pre[v] = u;  
			}
		}
	}
	cout << d[t] << endl;
	vector<int> path;
    while (t != s){
		path.push_back(t);
		t=pre[t];
	}
	path.push_back(s);
	reverse(path.begin(),path.end());
	for (int i=0;i<path.size();i++){
	    cout << path[i]<< " ";
}
}
int main(){
	setIO("SHORTESTPATH");
	readin();
	dijkstra(s,t);
	return 0;
	//fi.close();
	//fo.close();
}

