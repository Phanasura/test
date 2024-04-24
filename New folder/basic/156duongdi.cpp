#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,m,a[1001][1001];
void readin(){
	fi >> n >> m;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			a[i][j]=1;
		}
	}
}
void solve(){
	for (int i=n-1;i>=1;i--){
		for (int j=m-1;j>=1;j--){
			a[i][j]=a[i+1][j]+a[i][j+1];
		}
	}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			cout << a[i][j]<< " ";
		}
		cout << endl;
	}
	cout << endl << a[1][1];
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
