#include <bits/stdc++.h>
using namespace std;
//ifstream fi("test.txt");
//ofstream fo("kq.txt");
ifstream fi("dfs1.inp");
ofstream fo("dfs1.out");
int n,m,x,y;
vector <int> v[100000];
bool visited[100000];
void readin(){
	fi >> n >> m;
	for (int i=1;i<=m;i++){
		fi >> x >> y;
		v[x].push_back(y);
		v[y].push_back(x);  
	}
	memset(visited,false,sizeof(visited));
}

void dfs(int u){
	visited[u]=true;
	fo << u << " ";
	for (int j=0;j<v[u].size();j++){
		if (!visited[v[u][j]])
			dfs(v[u][j]);
	}
}
int main(){
	readin();
	dfs(1);
	return 0;
	fi.close();
	fo.close();
}


