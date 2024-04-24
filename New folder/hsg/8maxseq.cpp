#include <bits/stdc++.h>
#include <fstream>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int n,a[1001],s,maxs;
void nhap(){
	fi >> n;
	for (int i=0;i<n;i++){
		fi >> a[i];
	}
}
void xuat(){
	fo << maxs;
}
void solve(){
	maxs=0;
	for (int i=0;i<n;i++){
		for (int j=i;j<=n;j++){
			s=0;
			for (int k=i;k<=j;k++){
				s=s+a[k];
		    }
            if (maxs<s){
            	maxs=s;
			}			
		}
	}
	xuat();
}
int main(){
	nhap();
	solve();
	return 0;
	fi.close();
	fo.close();
}
