#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");

int n,a[1001],res=0;
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++){
		fi >> a[i];
	}
}
int findmax(int a[],int n){
	res=a[1];
	for (int i=1;i<=n;i++){
		res=max(res,a[i]);
	}
	return res;
}
void solve(){
	int boiso=findmax(a,n);
	for (int i=1;i<=n;i++){
		if (boiso%a[i]==0) continue;
		else{
			boiso*=2;
			int i=0;
		}
	}
	cout<< boiso;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
/*
inp:
5
12 6 2 8 3
out:
24
*/

