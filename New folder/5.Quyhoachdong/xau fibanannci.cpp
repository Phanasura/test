#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int f[1001],t;
void readin(){
	f[1]=f[2]=1;
	for (int i=3;i<=92;i++){
		f[i] = f[i-1]+f[i-2];
	}
}
void solve(){
	int n,i;
	fi >> n >> i;
	while (n > 2){
		if (i <= f[n-2]) n-=2;
		else{
			i-=f[n-2];
			n-=1;
		}
	}
	if (n==1) cout << "A" << endl;
	else cout << "B" << endl;
}
int main(){
	readin();
	fi >> t;
	while (t--){
		solve();
	}
	return 0;
	fi.close();
	fo.close();
}

