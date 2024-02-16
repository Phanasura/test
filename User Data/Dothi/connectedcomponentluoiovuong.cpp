#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
char a[1001][1001];
bool visited[1001][1001];
int n ,m;
int bi[4]={0,1,0,-1};
int bj[4]={1,0,-1,0};
void readin(){
	fi >> n >> m;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			fi >> a[i][j];
		}
	}
	memset(visited, false, sizeof(visited));
}

void dfs(int i, int j){
	fo << i << " "<< j<< endl;
	visited[i][j]= true;
	for (int k=0;k<4;k++){//neu da khai bao phan tu mang thi phai cho tu 0->4
		int i1=i+bi[k];
		int j1=j+bj[k];
		if (i1>=1 && i1 <=n && j1>=1 && j1<=m && a[i1][j1]=='x' && !visited[i1][j1]) // bai mang 2 chieu thi danh dau cung phai 2 chieu
		    dfs(i1,j1);
	}
}
/*
void bfs(int i,int j){
	queue<pair<int,int> > q;
	q.push({i,j});
	visited[i][j] = true;
	while (!q.empty()){
		pair<int,int> v = q.front();
		q.pop();
		fo << i << " "<< j<< endl;
		for (int k=0;k<4;k++){
			int i1 = v.first + bi[k];
			int j1 = v.second + bj[k];
			if (i1>=1 && i1 <=n && j1>=1 && j1<=m && a[i1][j1]=='x' && !visited[i1][j1]){
				q.push({i1,j1});
				visited[i1][j1]=true;
			}
		}
	}
}*/
void solve(){
	int cnt=0;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			if (a[i][j]=='x' && !visited[i][j]){
				++cnt;
				dfs(i,j);
			}
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
/*
inp :
6 6
x x x o o o
o o x o o o
o x x x x o
o o o o o x
x x o x o x
x o x x o x
out :
1 1
1 2
1 3
2 3
3 3
3 4
3 5
3 2
4 6
5 6
6 6
5 1
5 2
6 1
5 4
6 4
6 3
4
*/


