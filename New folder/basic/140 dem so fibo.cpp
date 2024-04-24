#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
double l,r;
void readin(){
	fi >> l >> r;
}
void solve(){
	int dem;
	double b=1.0,a=1.0;
	if (l==1){
		dem=2;
	}
	else if (l==2){
		dem=1;
	}
	while (b<=r){ //1 1 2 3 5 8 13
		b=b+a; // so fibo moi = fibo gan cu + fibo gan cu cu
		a=b-a; //fibo gan cu cu = fibo moi - fibo  gan cu  cu;
		if (b>=l) dem++;
	}
	cout << dem-1;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
