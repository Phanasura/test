#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
//ifstream fi("dfs1.inp");
//ofstream fo("dfs1.out");
int n,m,x,y;
vector <int> v[1000];
bool visited[1000];
void readin(){
	fi >> n >> m;
	for (int i=1;i<=m;i++){
		fi >> x >> y;
		v[x].push_back(y);
	//	v[y].push_back(x);  => do thi co huong
	}
	memset(visited,false,sizeof(visited));
	for (int i = 1; i <= n; i++){
		sort(v[i].begin(), v[i].end());
	}
}

void dfs(int u){
	fo << u << " ";
	visited[u]=true;
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
/*
inp:
9 10
1 2
1 3
1 5
2 4
3 6
3 7
5 8
6 7
8 9
9 3
out:
1->2->4->3->6->7->5->8->9->
*/

