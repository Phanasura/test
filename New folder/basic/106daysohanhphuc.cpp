#include <bits/stdc++.h>
using namespace std;
bool visited[1001];
int n,a[1001];
void readin(){
	cin >> n;
	memset(visited,false,sizeof(visited));
}
bool kt(int x){
	if (x<2) return false;
	else {
		for (int i=2;i<=sqrt(x);i++){
			if (x%i==0) return false;
		}
	}
	return true;
}
bool check(int vt){
	for (int i=n;i>=vt;i--){
		if (visited[i] && i%vt==0) return true;
	}
	return false;
}
void solve(){ 
	visited[n]=true;
	for (int i=n-1;i>=1;i--){
		if (kt(i) || check(i)) visited[i]=true;
	}
	for (int i=n;i>=1;i--){
		if (visited[i]) cout<<i<<" ";
	}
}
int main(){
	freopen("test.txt","r",stdin);
	readin();
	solve();
	return 0;
}
