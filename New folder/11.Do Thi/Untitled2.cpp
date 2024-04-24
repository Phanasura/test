#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

void readin(){
	cin >> n >> m;
	cin >> s1 >> s2;
	cin >> e1 >> e2;
}

void solve(){
	
}

int main(){
	//setIO("QUANMA");
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
