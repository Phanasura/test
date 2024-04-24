#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("TMAX.OUT");
int n,a[1001000],dp[1000001],kq1,kq2,t,sum;
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++) fi >> a[i];
	memset(dp,0,sizeof(dp));
	sum=0;
	kq2=0;
	kq1=0;
}
int daycon(){
	for (int i=1;i<=n;i++){
    	kq1 = max(kq1, max(kq1 + a[i], a[i]));
	}
	return  kq1;
}
int doancon(){
	for (int i=1;i<=n;i++){
		sum = max(a[i],sum+a[i]);
		kq2 = max(sum,kq2);
	}
	return kq2;
}
void solve(){
	kq1 = daycon();
	kq2 = doancon();
	cout<< kq1 << " "<< kq2;
}
int main(){
	fi >> t;
	while (t--){
		readin();
	    solve();
	    //else fo <<0 << " "<< 0;
	    cout << endl;
	}
	return 0;
	fi.close();
	fo.close();
}
