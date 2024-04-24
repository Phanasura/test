#include <bits/stdc++.h>
using namespace std;
int dem,n,t[1001],j=0,spt,num[1001],sl[1001],s;
void readin(){
    cin >> n;
}
bool kt(int x){
	if (x<2) return false;
	else {
		for (int i=2;i<=sqrt(x);i++){
			if (n%i==0) return false;
		}
	}
	return true;
}
void demphanphoi(int t[],int j){
    int i=1;
    spt=0;
	do {
    	int key=t[i];
    	i++;
    	dem=1;
    	while ((key==t[i]) && (i<=j)){
    		i++;
    		dem++;
		}
		spt++;
		num[spt]=key;
		sl[spt]=dem;
	}while (i<=j);
}
void solve(){
    if (kt(n)) cout<< n;
    else{
    	for (int i=2;i<=n;i++){
    	    while (n%i==0){
    	    	if (kt(i)){
    	    	    j+=1;
    	    	    t[j]=i;
    	    	    n=n/i;
			    }
			}
	    }
	}
    demphanphoi(t,j);
    for (int i=1;i<=spt;i++) s=s+num[i];
    cout << s;
}
int main(){
	freopen("test.txt","r",stdin);
	readin();
	solve();
	return 0;
}
