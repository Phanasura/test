#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
void setIO(string name = "") { 
	ios_base::sync_with_stdio(0);
	cin.tie(0);  
	if (!name.empty()) {
		freopen((name + ".in").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}
vector <int> v[1001];
int n,m,x,y;
bool visited[1001];
void readin(){
	cin >> n >> m;
	for (int i=1; i<= m;i++){
		cin >> x >> y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	memset(visited,false,sizeof(visited));
}
void dfs(int u){
	visited[u] = true;
	for (int i=0;i<v[u].size();i++){
		if (!visited[v[u][i]]){
			dfs(v[u][i]);
		}
	}
}
void solve(){
	int cnt=0;
	for (int i=1;i<=n;i++){
		if (!visited[i]){
			cnt++;
			dfs(i);
			cout << i-1 << " " << i<< endl;
		}
	}
	cout << cnt -1 << endl;
}

int main(){
	//setIO("test");
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
