#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int n,a[N],sm=0,du;
int main(){
	freopen("Maxval.inp","r",stdin);
	freopen("Maxval.out","w",stdout);
	cin>>n;
	for (int i=1; i<=n;i++) 
		cin>>a[i];				
	sort(a+1,a+1+n);
	int j=1, i=n;
	while (j<i){
		du=a[i]%a[j];
		sm=max(sm,du);
		j++; 
		i--;
	}
	cout<<sm;
}

