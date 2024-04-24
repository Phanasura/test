#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int a[1000][1001],n,m,f[1000][1001],res;
void readin(){
	cin >> n >>m;
}
void solve(){
    for (int i=0;i<25;i++) f[i][0]=1;
    for (int i=0;i<25;i++) f[0][i]=1;
    f[0][0]=0;
    for (int i=0;i<25;i++){
    	for (int j=0;j<25;j++){
    		if (i==0 || j==0) continue;
    		else  f[i][j]=f[i-1][j]+f[i][j-1];
		}
	}
	cout << f[n][m];
    
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
3 2
out :
10
*/
