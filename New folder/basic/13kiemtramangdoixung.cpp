#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,a[1001];
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++) fi >> a[i];
}
void solve(){
	int i=1,flag=1;
	while (i<n){
		if (a[i]!=a[n]) flag=0;
		i++; 
		n--;
	}
	if (flag) cout << "YES";
	else cout << "NO";
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
