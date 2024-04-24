#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,m,a[1001],b[1001],t[1001],spt=0;
bool ca[1001],cb[1001];
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++) fi >> a[i];
	fi >> m;
	for (int i=1;i<=m;i++) fi >> b[i];
}
void solve(){
	for (int i=1;i<=n;i++){
	    for (int j=1;j<=m;j++){
			if (a[i]==b[j]){
                ca[i]=true;
				cb[j]=true;	
			}
		}
	}
	for (int i=1;i<=n;i++){
		if (!ca[i]) {
			t[++spt]=a[i];
		} 
	}
	for (int i=1;i<=m;i++){
		if (!cb[i]) {
			t[++spt]=b[i];		
		} 
	}
	for (int i=1;i<=spt;i++) cout << t[i]<<" ";
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
