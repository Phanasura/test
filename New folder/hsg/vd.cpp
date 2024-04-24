#include <bits/stdc++.h>
using namespace std;
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		ifstream nhap(name + ".txt");
		//ofstream xuat(name + ".out");
	}
}
int n;
void readin(){
	nhap >> n;
}

void solve(){
	xuat << n;
}

int main(){
	setIO("test");
	readin();
	solve();
	return 0;

}
