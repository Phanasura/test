#include <bits/stdc++.h>
using namespace std;

ifstream fi("lis1.inp");
ofstream fo("lis1.out");

long long n,a[1000000],i,dem=0,maxi=0,b[1000000];

void nhap(){
	fi >> n;
	for (i=1;i<=n;i++){
		fi >> a[i];
	}
}
void solve(){
	b[1]=1;
    for (i=1;i<=n;i++) {
    	if (a[i]>=a[i-1]){
		    b[i]=b[i-1]+1; 
		    if (b[i]>dem) {
    		    dem=b[i]; 
			    maxi=i;
		    }
	    }
		else b[i]=1;
	}
	fo << dem <<endl;
	for (i=maxi-dem+1;i<=maxi;i++) 
	    fo<<a[i]<<" ";		
}
int main(){
	nhap();
	solve();
	return 0;	
	fi.close();
	fo.close();
}
