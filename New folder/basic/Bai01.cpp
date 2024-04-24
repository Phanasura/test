#include <bits/stdc++.h>
using namespace std;
int n,m;
bool kt(int n){
	if (n<2) return false;
	for (int i=2;i<=sqrt(n);i++) 
	    if (n%i==0) return false;
	return true;
}
void pt(int n){
	if (kt(n)) cout << n << " la so nguyen to";
	else  {
		for (int i=2;i<=n;i++){
			//dem=0;
			int spt=1;
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
	cin >> n;
	pt(n);
    return 0;
}
