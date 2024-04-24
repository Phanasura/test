#include <bits/stdc++.h>
using namespace std;

int n,dem;
void readin(){
	cin >> n;
}
int ucln(int a,int b){
	if (b==0) return a;
	else {
		return ucln(b,a%b);
	}
}
void solve(){
	dem=0;
	for (int i=1;i<=n-1;i++){
		if (ucln(n,i)==1) dem+=1;
		//cout << i<<ucln(n,i)<< " ";
	}
	cout << dem;
}
int main(){
	freopen("test.txt","r",stdin);
	readin();
	solve();
	return 0;
}
