#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int dem,n,a[1001],fibo[1001],spt;
void readin(){
	fi >>n;
}
void taofibo(){
	fibo[1]=1;
	fibo[2] =1;
	dem=2;
	for (int i=3;i<=n;i++){
		fibo[i]=fibo[i-1]+fibo[i-2];
		dem+=1;
		if (fibo[i]>n) break;
	}
}
void solve(){
    taofibo();
    int res=n;
    spt = 1;
    //for (int i=1;i<=dem;i++) cout << fibo[i]<< " ";
    for (int i=dem;i>=1;i--){
    	if (fibo[i]<=res){
    		res=res-fibo[i];
    		a[spt]=i;
    		spt+=1;
		}
	}
	spt--;
	cout << n << "=";
	for (int i=1;i<=spt;i++) {
		if (fibo[a[i]]&&i!=spt){
			cout << fibo[a[i]]<< "+";
		}
		else {
			if (fibo[a[i]]) cout << fibo[a[i]];
		}
	}
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
