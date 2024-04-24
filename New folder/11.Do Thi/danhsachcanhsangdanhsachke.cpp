#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int n,m,x,y,a[1000][1000];
vector <int> v[1000];
void readin(){
	fi >> n >> m;
	for (int i=1;i<=m;i++){
		fi >> x >> y;
		v[x].push_back(y);
		//v[y].push_back(x);
	}
}
void solve(){
	for (int i=1;i<=n;i++){
		fo << i<<" : ";
		for (int j=0;j<v[i].size();j++){
			fo << v[i][j] << " ";
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
1 : 2 3 4 
2 : 1 3 4 5 
3 : 1 2 4 5 
4 : 1 2 3 5 
5 : 2 3 4 
*/

