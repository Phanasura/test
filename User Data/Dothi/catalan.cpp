#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
string s;
void readin(){
	fi >> s;
}
void solve(){
	stack <char> t;
	for (int i=0;i<s.length();i++){
		if (s[i]=='{'){
			t.push(s[i]);
		}
		if (s[i]=='}'){
			t.pop();
		}
	}
	if (!t.empty()) cout << "no";
	else cout << "yes";
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
