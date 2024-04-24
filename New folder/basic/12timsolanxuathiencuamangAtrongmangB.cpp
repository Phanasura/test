#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,m,a[1001],b[1001],start,flag,dem=0;
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++) fi >> a[i];
	fi >> m;
	for (int i=1;i<=m;i++) fi >> b[i];
}

void solve(){
	for (int i=1;i<=m;i++){
		if (a[1]==b[i]){
			start=i+1;
			flag=1; //co lenh
			for (int j=2;j<=n;j++){
				if (a[j]!=b[start]){
					flag=0;
					break;
				}
				else start++;
			}
			if (flag==1) {
				dem++;
			}
		}
	}
	cout << dem;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
