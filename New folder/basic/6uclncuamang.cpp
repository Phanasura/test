#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");

int n,a[1001],res;
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++){
		fi >> a[i];
	}
}
int gcd(int a,int b){
	if (b==0) return a;
	else return(b,a%b);
}

void solve(){
	res=a[0];
	for (int i=1;i<=n;i++){
		res=gcd(a[i],res);
	}
	cout<< res;
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
24 30 36 18 42
out:
6
*/

