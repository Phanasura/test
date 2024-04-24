#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,a[1001][1001],b[1001];
void readin(){
	fi >> n;
	int x,y;
	while (!fi.eof()){
		fi >> x >> y;
		a[x][y]=1;
	}
}
void qhd(){
	for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
        	if (a[i][j] == 1) a[i][j]=a[i-1][j-1]+1; 
        	else {
        		a[i][j] = max(a[i-1][j],a[i][j-1]);
			}
		}
	}
}
void track(){
	int i=n,j=n;
    while (a[i][j]!=0){
    	while (a[i-1][j]==a[i][j] && i>1) i--;
		while (a[i][j-1]==a[i][j] && j>1) j--;
		b[i] = j;
		i-=1;
		j-=1;
	}
	cout << a[n][n]<< endl;
	for (int i=1;i<=n;i++){
		if (b[i]!=0){
			cout << i << " "<< b[i]<< endl;
		}
	}
}
void solve(){
	qhd();
    track();
	/*for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}*/
}

int main(){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	readin();
	solve();
	return 0;
	fi.close();
}
/*
inp:
5
3 4
4 2
4 4
5 1
5 2
5 3
3 2
5 5
1 3
2 1
*/
