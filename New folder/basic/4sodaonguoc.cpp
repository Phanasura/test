#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");

int n;
void readin(){
	fi >> n;
}

void solve(){
	int m=0;
	do {
		int res=n%10;
		n=n/10;
		m=m*10+res;
	}while (n!=0);
	cout << m;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
/*
234
out: 432
*/
