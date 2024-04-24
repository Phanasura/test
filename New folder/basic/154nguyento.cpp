#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int spt,d,a[1001],n,t;
void readin(){
	fi >> n;
	spt=0;
}
void demuoc(){
    d=2;
	for (int i=2;i<=sqrt(n);i++){
		if (n%i==0){
			d+=2;
		}
	}
	if (sqrt(n)==int(sqrt(n))) d--;
}
bool kt(int x){
	if (x<2) return false;
	for (int i=2;i<=sqrt(x);i++){
		if (x%i==0) return false;
	}
	return true;
}
void phantich(){
	/*if (kt(n)) cout << n;
	else{
		for (int i=2;i<=n;i++){
		    spt+=1;
		    while (n%i==0){
			    if (kt(i)){
				    n/=i;
			        cout << i ;
			        if (n>1) cout << "*";
			    }
	    	}
    	}
	}*/
	int i=1;
	while (n>1){
		i++;
		while (n%i==0){
			cout << i;
			n/=i;
			if (n>1) cout<<"*";
		}
	}
}
void solve(){
	demuoc();
	cout << d<<" ";
	phantich();
	cout << endl;
}
int main(){
	fi >> t;
	while (t--){
		readin();
		solve();
	}
	return 0;
	fi.close();
}
