#include <bits/stdc++.h>
using namespace std;
long long kq,k,n;
ifstream fi("SOHOC.inp");
ofstream fo("SOHOC.out");
void readin(){
	fi >> n;
}
bool kt(long long x){
	if (x<2) return false;
	for (long long i=2;i<=sqrt(x);i++){
		if (x%i==0) return false;
	}
	return true;
}
void solve(){
	kq=0;
	if (sqrt(n) == long(sqrt(n))) {
		k=sqrt(n);
	}
	else{
		k=long(sqrt(n))+1;
		
	}
	long long i = k;
	while (i<n){
		if (kt(i)) {
			kq = i*i;
			break;
		}
		i++;
	}
	fo << kq;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
