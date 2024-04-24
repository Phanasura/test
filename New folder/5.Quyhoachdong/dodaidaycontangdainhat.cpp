#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int a[1000],n,dp[10000],res,t[1001],jmax,g=0;
void readin(){
	cin >> n;
	for (int i=0;i<n;i++){
		cin >> a[i];
	}
}
void solve(){
	for (int i=0;i<n;i++){
		dp[i]=1;
		for (int j=0;j<i;j++){
			if (a[i]>a[j]) dp[i]=max(dp[i],dp[j]+1);
			/*if (res<dp[i]){
				res=dp[i];
			    jmax=j;
			}*/
			
		}
		//cout << dp[i]<< " ";
		//t[i]=jmax;
		res = max(res,dp[i]);
	}
	cout << res;
	
	/*
	cout << endl << res << " "<< jmax<< endl;
	for (int i=0;i<n;i++){
    	cout << a[i]<< " ";
	}
	cout << endl;
	for (int i=0;i<n;i++){
    	cout << dp[i]<< " ";
	}
	cout << endl;
    for (int i=0;i<n;i++){
    	cout << t[i]<< " ";
	}
	cout << endl;
	int max=0;
	for (int i=0;i<n;i++){
		if (dp[i]>dp[max])
		max=i;
	}
	while (true){
		int i=max;
		cout << a[i] << " ";
		max = t[i];
		if (t[max]==0){
			cout << a[max] << " ";
			break;
		}
	}*/
}
int main(){
	readin();
	solve();
	return 0;
	//fi.close();
	//fo.close();
}
/*
inp:
6
1 2 5 4 6 2
out:
4*/
