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
	vector<int> a;
	while (n){
		a.push_back(n%10);
		n/=10;
	}
	reverse(a.begin(),a.end());
	long long res = 0;
	for (int i=0;i<a.size();i++){
		long long tmp = 0;
		for (int j=i;j<a.size();j++){
			tmp = 10*tmp+a[j];
			res += tmp;
		}
	}
	cout << res;
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
1234
out 1670 giai thich : (1670 = 1+2+3+4+12+23+34+123+234+1234)
inp 421
out 491*/
