#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inP").c_str(), "r", stdin); 
		//freopen((name + ".out").c_str(), "w", stdout);
	}
}
int n;
void readin(){
	cin >> n;
}

void solve(){
	long long ugly[n];
	long long i2=0,i3=0,i5=0;
	ugly[0] = 1;
	for (int i=1;i<n;i++){
		ugly[i] = min(ugly[i2]*2,min(ugly[i3]*3,ugly[i5]*5));
		if (ugly[i] == ugly[i2]*2){
			i2 = i2+1;
		}
		if (ugly[i] == ugly[i3]*3) i3 = i3+1;
		if (ugly[i] == ugly[i5]*5) i5 = i5+1;
	}
	cout << ugly[n-1];
}

int main(){
	//setIO("TEN FILE");
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
inp:
2
10
4
out:
12 
4
*/
