#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int a[1001],spt,n;
void readin(){
	fi >> n;
}
bool kt(int n){
	if (n<2) return false;
	for (int i=2;i<=sqrt(n);i++) 
	    if (n%i==0) return false;
	return true;
}
void solve(){
	if (kt(n)) cout << n << " la so nguyen to";
	else  {
		for (int i=2;i<=n;i++){
			//dem=0;
			spt=1;
			while (n%i==0){
				//dem+=1;
				if (kt(i)){
				    n/=i;
				    cout << i << " ";
				}
			}
		}
	}

}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
