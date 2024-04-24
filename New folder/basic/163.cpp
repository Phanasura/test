#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int x,y,a[1001][1001],n,m;
vector <int> v[1001];
bool visited[1001];
int parent[1001];
int buoc = 0;
void readin(){
	fi >> n >> m;
	memset(a,sizeof(a),0);
	for (int i=1;i<=m;i++){
		fi >> x >> y;
		v[x].push_back(y);
	}
	memset(visited, false, sizeof(visited));
	memset(parent, 0, sizeof(parent));
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
			    buoc += 1;
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
	bfs(1);
	cout <<  buoc-1<< endl;
	//findway(1,n);
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
