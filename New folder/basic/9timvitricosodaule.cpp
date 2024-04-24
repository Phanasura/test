#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,a[1001];
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++) fi >> a[i];
}
int timsole(int x){
	while (x>=10){
		int du=x&10;
		x=x/10;
	}
	return x;
}
void solve(){
	for (int i=1;i<=n;i++){
		if (timsole(a[i])%2!=0)
		   cout << a[i]<< " ";
	}
}
int main(){
	readin();
	solve(); 
	return 0;
	fi.close();
}
/*
inp:
6
30 52 20 11 28 45
out:
30 52 11
*/

