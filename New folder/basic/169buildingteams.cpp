#include <bits/stdc++.h>
using namespace std;

int color[100], a, b, n, m;
bool visited[100];
vector<int> v[1001];

void readin(){
	cin >> n >> m;
	for (int i = 1 ; i <= m ; i++){
		cin >> a >> b;
		color[a] = 1;
		color[b] = 2;		
		v[a].push_back(b);
		v[b].push_back(a);
	}
	memset(visited, false, sizeof(visited));
}

bool dfs(int u,int cu){
	visited[u] = true;
	for (int i = 0 ; i < v[u].size() ; i++){
		if (color[v[u][i]] == cu){
			return false;
		}
		if (!visited[v[u][i]]){
		    dfs(v[u][i], color[v[u][i]]);
		}
	}
	return true;
}

void solve(){
	for (int i = 1 ; i<=n ; i++){
		if (!visited[i] && !dfs(i, color[i])){
			cout << "Impossible";
			return;
		}
	}
	for (int i = 1 ; i<=n ; i++){
		cout << color[i] << " ";
	}
}

int main(){
	readin();
	solve();
	return 0;
}
