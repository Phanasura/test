#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,a[1001],m,b[1001],j=1;
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++) fi >> a[i];
	fi >> m;
	for (int i=1;i<=m;i++) fi >> b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
}
void solve(){
	int kt=1;
	if (n!=m) cout << "NO";
	else {
		for (int i=1;i<=n;i++){
	        if (a[i]!=b[i]) kt=0;	
	    }
	    if (kt==1) cout << "YES";
	    else cout<<"NO";
	}
	/*for (int i=1;i<=n;i++) cout<< a[i] << " ";
	cout << endl;
	for (int i=1;i<=m;i++) cout << b[i]<< " ";*/
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
