#include <bits/stdc++.h>
using namespace std;
int n,m;
bool check;
void readin(){
	cin >> n;
	cin >> m;
}
bool kt(int x){
	if (x<2) return false;
	else {
		for (int i=2;i<=sqrt(x);i++){
			if (x%i==0) return false;
		}
	}
	return true;
}
void solve(){
	int c=max(m,n);
	check=false;
	for (int i=2;i<=sqrt(c);i++){
		if (kt(i) && m%i==0 && n%i==0){
			check=true;
			cout << i<< " ";
			break;
		}
		else 
		if (kt(i) && (m%i!=0 && n%i==0 || m%i==0 && n%i!=0)){
			check=false;
			break;
		}
	}
	if (check==1) cout<< "YES";
	else cout<<"NO";
}
int main(){
	freopen("test.txt","r",stdin);
	readin();
	solve();
	return 0;
}
