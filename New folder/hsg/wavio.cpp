#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ifstream fi("Wavio.inp");
//ofstream fo("wavio.out");
//ifstream fi("test.txt");
ofstream fo("Wavio.Out");
const int mn = 1e7;
ll n,a[mn],l1[mn],l[mn],i,j,kq,t,l2[mn];
void readin(){
	cin >> n;
	for (i=1;i<=n;i++){
		cin >> a[i];
	}
}
int dct(ll a[]){
	int maxx=0;
	for (i=1;i<=n;i++) l[i]=1;
	for (i=1;i<=n-1;i++){
		for (j=i+1;j<=n;j++){
			if ((a[i]<a[j])&&(l[j]<l[i]+1)) l[j]=l[i]+1;
			if (maxx<l[j]) maxx=l[j];
		}
	}
	return maxx;
}
void ktdcg(ll a[]){
	int maxx=0; l1[n]=1;
	for (i=1;i<=n;i++) l1[i]=1;
	for (i=n-1;i>=1;i--){ t=0;
		for (j=i;j<=n;j++){
			if ((a[i]>a[j])&&(l1[j]>t)) t=l1[j];
			if (maxx<l1[j]) maxx=l1[j];
		}
		l1[i]=t+1;
	}
}
ll dcg(ll a[]){
	int maxx=0;
	for (i=1;i<=n;i++) l2[i]=1;
	for (i=1;i<=n-1;i++){
		for (j=i+1;j<=n;j++){
			if ((a[i]>a[j])&&(l2[j]<l2[i]+1)) l2[j]=l2[i]+1;
			if (maxx<l2[j]) maxx=l2[j];
		}
	}
	return maxx;
}
void solve(){
	int st=dct(a);
	int sg=dcg(a);	
	ktdcg(a);
    if ((n==st)||(n==sg)||(st==1)||(sg==1)) fo << 1;
	else {
		for ( i=1;i<=n;i++) kq=max(kq,l[i]+l1[i]-1);
        //for (int i=1;i<=n;i++) cout<<l[i]<<" "<<l1[i]<<endl;
	    cout << kq;
	}
	
	//for (int i=1;i<=n;i++) cout << l2[i]<<" ";
	
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
    
