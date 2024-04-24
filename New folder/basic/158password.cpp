#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");

int n,s,d;

void readin(){
	fi >> n >> s;
}

void solve(){
	if (s<=n*9){
		while ((s/9)>=1){
			cout << 9;
			s=s-9;
			d++;
		}
		cout << s;
		for (int i=1;i<=n-d-1;i++)
		 cout << 0;
	}
	else cout << -1;
}

int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
