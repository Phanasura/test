#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int n,m,x,y,a[1000][1000];
void readin(){
	fi >> n >> m;
	for (int i=1;i<=m;i++){
		fi >> x >> y;
		a[x][y]=a[y][x]=1;
	}
}
void solve(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			fo << a[i][j]<<" ";
		}
		fo << endl;
	}
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
5 9
1 2
1 3
1 4
2 3
2 4
2 5
3 4
3 5
4 5
out:
0 1 1 1 0 
1 0 1 1 1 
1 1 0 1 1 
1 1 1 0 1 
0 1 1 1 0 
*/

