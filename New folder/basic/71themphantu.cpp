#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,ptc,vtc,a[1001];
void readin(){
	fi >> n >> ptc ;
	for (int i=1;i<=n;i++) fi >> a[i];
	sort(a+1,a+n+1);
}
void timvitrichen(){
	for (int i=1;i<=n;i++) 
	if (ptc<=a[i]) {
		vtc=i;
		break;
	}
}
void chen(){
	n=n+1;
	for (int i=n;i>vtc;i--){
		a[i]=a[i-1];
	}	
	a[vtc]=ptc;
	//for (int i=1;i<=n;i++) cout << a[i] << " ";
}

void solve(){
    timvitrichen();
    chen();
    for (int i=1;i<=n;i++) cout << a[i] << " ";
    //cout << endl << vtc;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
