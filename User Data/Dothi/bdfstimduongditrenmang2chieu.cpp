#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int n,m,s1,s2,t1,t2;
char a[1001][1001];
bool visited[1001][1001];
pair <int,int> parent;
int bi[4]={0,1,0,-1};
int bj[4]= {1,0,-1,0};
int d[1001][1001];
void readin(){
	fi >> n >> m;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			fi >> a[i][j];
			if (a[i][j]=='A'){
				s1=i; s2=j;
			}
			if (a[i][j]=='B'){
				t1=i; t2=j;
			}
		}
	}
	//memset(visited, false, sizeof(visited));
	//memset(parent, 0, sizeof(parent));
}
bool dfs(int i,int j){
	fo << i <<" "<< j<< endl;
	if (a[i][j]=='B'){
		//visited[i][j]=true;
		return true;
	}
	
	visited[i][j]= true;
	for (int k=0;k<4;k++){
		int i1= i+bi[k];
		int j1= j+bj[k];
		if (i1<=n && i1 >=1 && j1<=m && j1>=1 && a[i1][j1]!='x' && !visited[i1][j1]){
			//parent[][]=
			if (dfs(i1,j1)) return true;
		}
	}
	return false;
	memset(visited,false,sizeof(visited));
}
/*
void findway(int s1, int s2, int t1,int t2){
	if (!visited[t1][t2]) fo << "Khong co duong di";
	else {
		vector<int> path;
		
	}
}*/
bool bfs(int i,int j){
	queue <pair <int,int> > q;
	q.push({i,j});
	visited[i][j]=true;
	d[i][j]=0;
	fo << i << " "<< j << endl;
	while (!q.empty()){
		pair<int,int> v = q.front();
		q.pop();
		for (int k=0;k<4;k++){
			int i1=v.first  +bi[k];
			int j1=v.second +bj[k];
			if (i1>=1 && i1<=n && j1>=1 && j1<=m && a[i1][j1]!='x' && !visited[i1][j1]){
				fo <<i1<< " "<< j1<< endl;
				d[i1][j1]=d[v.first][v.second]+1;
		        if (a[i1][j1]=='B')	return true;
				q.push({i1,j1});
				visited[i1][j1]= true;
			}
		}
	}
	return false;
}
void solve(){
	if (bfs(s1,s2)) {
		fo << "YES"<<endl;
		fo << d[t1][t2];
	}
	else fo << "NO"<< endl;
//	findway(s1,s2,t1,t2);
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
6 6
A o o x o o
o x o o o o
o x o o o o
o o o o x x
B o o o x o
o o o x x x
out:
1 1
1 2
2 1
1 3
3 1
2 3
4 1
2 4
3 3
4 2
5 1
YES
4
*/
