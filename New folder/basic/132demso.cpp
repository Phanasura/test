#include <bits/stdc++.h>
using namespace std;
int kq,k,a,b;
void readin(){
	cin >> a  >>  b;
}
bool kt(int x){
	if (x<2) return false;
	for (int i=2;i*i<=x;i++){
		if (x%i==0) return false;
	}
	return true;
}
void solve(){
	kq=0;
	if (sqrt(a)==int(sqrt(a))) {
		k=sqrt(a);
	}
	else{
		k=int(sqrt(a))+1;
		
	}
	for (int i=k;i<=int(sqrt(b));i++){
			if (kt(i)) kq+=1;
		}
	cout << kq;
}
int main(){
	freopen("test.txt","r",stdin);
	readin();
	solve();
	return 0;
}
