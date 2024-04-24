#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int n,m,x,y,a[1000][1000];
vector <int> v[1000];
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			fi >> a[i][j];
			if (a[i][j]==1){
				v[i].push_back(j);
				a[j][i]=0;
			}
		}
	}
}
void solve(){
	for (int i=1;i<=n;i++){
		fo << i << " : ";
		for (int j=0;j<v[i].size();j++){
			fo << v[i][j]<< " ";
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
5
0 1 1 1 0 
1 0 1 1 1 
1 1 0 1 1 
1 1 1 0 1 
0 1 1 1 0 
out:
1 : 2 3 4 
2 : 1 3 4 5 
3 : 1 2 4 5 
4 : 1 2 3 5 
5 : 2 3 4 
*/

