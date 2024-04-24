#include <bits/stdc++.h>

using namespace std;
ifstream fi("test.txt");
int n,res,a[1001],t;
int visited[1001];
void readin(){
	fi >> n;
	memset(visited,0,sizeof(visited));
	for (int i=1;i<=n;i++){
		fi >> a[i];
		res=max(res,a[i]);
	}
}
void xoa(int vt){
	t-=1;
	for (int i=vt;i<=t;i++){
		a[i]=a[i+1];
	}
}
void xuat(){
	for (int i=1;i<=t;i++){
		cout << a[i] << " ";
	}
}
void solve(){
	t=n;
	for (int i=1;i<=n;i++){
		if (res==a[i]) 	xoa(i);
	}
	xuat();
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
