#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,a[1001],imin;
bool visited[1001];
void readin(){
	fi >> n;
	memset(visited,false,sizeof(visited));
	for (int i=1;i<=n;i++) {
		fi >> a[i];
		if (a[i]>0) visited[i]=true;
	}
}
void solve(){
	imin=a[1];
	for (int i=1;i<=n;i++){
		if (imin>a[i] && visited[i]) imin=a[i];
	}
	memset(visited,false,sizeof(visited));
	for (int i=1;i<=n;i++){
		if (a[i]==imin) cout << i << " ";
	}
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}

