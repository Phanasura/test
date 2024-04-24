#include <bits/stdc++.h>
using namespace std;
//ifstream fi("test.txt");
//ofstream fo("kq.txt");
ifstream fi("lienthong.inp");
ofstream fo("lienthong.out");
int n,m,x,y;
vector<int> v[100001];
bool visited[100001];
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
	for (int j=0;j<v[u].size();j++){
		if (!visited[v[u][j]])
			dfs(v[u][j]);
	}
}

void solve(){  
    int cnt = 0 ;
    for (int i=1;i<=n;i++){
    	if (!visited[i]){
    		++cnt;
    		dfs(i);
		}
	}
	fo << cnt;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}

