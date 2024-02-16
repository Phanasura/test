#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int n,m,x,y,a[1000][1000];
vector <int> edge[1000];
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			fi >> a[i][j];
		}
	}
}
void solve(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			if (a[i][j]==1 && a[j][i]==1) 
			{
				fo << i << " "<< j<< endl;
				a[j][i]=0;
			}
		}
		
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
1 2
1 3
1 4
2 3
2 4
2 5
3 4
3 5
4 5
*/

