#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,a[1001],t,b[1001];
void readin(){
	fi >> n;
	for (int i=0;i<n;i++){
		fi >> a[i];
	}
}
bool kt(int b[],int t){
	for (int i=0;i<t-1;i++){
		if (b[i]>b[i+1]) return false;
	}
	return true;
}
void xuat(){
	for (int i=0;i<t;i++) cout << b[i]<< " ";
	cout << endl;
}
void solve(){
	for (int i=0;i<n;i++){
		for (int l=1;l<=n;l++){
			t=0;
			for (int j=i;j<l;j++){
				b[t]=a[j];
				t++;
			}
			if (kt(b,t)) xuat();
		}
	}
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
