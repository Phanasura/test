#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int n,t,a;
vector <string> v;
void readin(){
	fi >>n;
}

void solve(){
	queue<string> q;
	
	q.push("9");
	v.push_back("9");
	while (v.size()<10000){
		string top =  q.front();
		q.pop();
		v.push_back(top+"0");
		v.push_back(top+"9");
		q.push(top+"0");
		q.push(top+"9");
		
	}
}
int main(){
	fi >> t ;
	solve();
	while (t--){
		readin();
		for (int i=0;i<n;i++){
			a=stoll(v[i]);
			if (a%n==0){
				fo << a ;
				break;
			}
		}
		fo << endl;
	}
	return 0;
	fi.close();
	fo.close();
}
