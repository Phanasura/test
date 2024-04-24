#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,a[1001],csmin,so,b[1001],chuso;
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++) fi >> a[i];
	memset(b,0,sizeof(b));
}
void demchuso(){
	for (int i=1;i<=n;i++){
		so=abs(a[i]);
		while (so != 0){
			chuso=so%10;
			so=so/10;
			b[chuso]+=1;
		}
	}
}
void solve(){
	demchuso();
	csmin=(abs(a[1]))%10;
	//cout << csmin;
	for (int i=0;i<10;i++){
		if (b[i]!=0){
			csmin = (b[csmin]>b[i])? i:csmin; 
		}
	}
	cout << csmin;
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
223 335 552 425 325
out :
4
*/
