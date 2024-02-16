#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int n , m, x, y,s,t;
vector<int> v[1001];
bool visited[1001];
int parent[1001];
void readin(){
	fi >> n >> m >> s >> t;
	for (int i=1;i<=m;i++){
		fi >> x >> y;
		v[x].push_back(y);
	//	v[y].push_back(x);
	}
	memset(visited, false, sizeof(visited));
	memset(parent, 0, sizeof(parent));
}
void dfs(int u,int t){
	//cout << u << " ";
	//if (visited[t]) return;
	visited[u]=true;
	for (int j=0;j<v[u].size();j++){
		if (!visited[v[u][j]]){
			parent[v[u][j]] = u;
			dfs(v[u][j],t);
		}  
	}
}
void bfs(int u){
	queue <int> q;
	q.push(u);
	visited[u]=true;
	while (!q.empty()){
		int x=q.front();
		q.pop();
		for (int i=0;i<v[x].size();i++){
			if (!visited[v[x][i]]){
				q.push(v[x][i]);
			    visited[v[x][i]]=true;
			    parent[v[x][i]] = x;
			}
		}
	}
}
void findway(int s, int t){
	if (!visited[t]) cout << "Khong co duong di";
	else {
		cout << "Co duong di la: "<< endl;
		vector<int> path;
		while (t != s){
		    path.push_back(t);
		    t=parent[t];
	    }
	    path.push_back(s);
	    reverse(path.begin(),path.end());
	    for (int i=0;i<path.size();i++){
	        cout << path[i]<< " ";
		}
	}
	
}
void solve(){
	dfs(s,t);
	//bfs(s);
	//for (int i=1;i<=n;i++) fo << parent[i]<< " ";
	findway(s, t);
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
inp:
6 9 1 6
1 2
1 3
2 3
2 5
3 4
3 5
4 5
4 6
5 6
out:
Co duong di la:
1 2 3 4 5 6
*/

