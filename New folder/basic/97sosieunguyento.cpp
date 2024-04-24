#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int dem,n,t[1001];
void readin(){
	fi >>n;
}
bool kt(int x){
	if (x<2) return false;
	else {
		for (int i=2;i<=sqrt(x);i++)
		    if (x%i==0) return false;
	}
	return true;
}
bool ktsnt(int x){
	while (x!=0){
		if (kt(x)) x=x/10;
		else return false;
	}
	return true;
}
void solve(){
	int a=1;
    for (int i=1;i<n;i++){
    	a=a*10;
	}
	dem=0;
	int b=a*10-1;
	for (int i=a;i<=b;i++){
		if (ktsnt(i)) {
			dem=dem+1;
		}
	}
	cout << dem << endl;
	for (int i=a;i<=b;i++){
		if (ktsnt(i)) {
			cout << i << " ";
		}
	}
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
