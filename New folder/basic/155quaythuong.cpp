#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,m,a[1001],f[1001],b[1001];
void readin(){
	fi >> n >> m;
	for (int i=1;i<=n;i++){
		fi >> a[i];
		f[a[i]]+=1;
	}
	for (int i=1;i<=m;i++){
		fi >> b[i];
		if (f[b[i]]!=0){
			f[b[i]]=0;
		}
	}
}
void solve(){
	int kq=0;
	for (int i=1;i<=n;i++){
		if (f[a[i]]!=0){
			cout << a[i]<< " ";
			kq=max(kq,a[i]*f[a[i]]);
		}
	}
	cout << endl << kq;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
