#include <bits/stdc++.h>
using namespace std;

ifstream fi("appdiv.inp");
ofstream fo("appdiv.out");

long long s,tongchung,i,a[1000000];
int n;
bool kt;

void nhap(){	
	fi >> n;
	for (i=1;i<=n;i++){
		fi >> a[i];
		s=s+a[i];
	}
	
}

void solve(){
	kt=false;
	tongchung=s;
	for (i=1;i<=n;i++){
		if (a[i]>tongchung/2){
			s=s-a[i];
			kt=true;
		}
	}
	if (kt) fo << ((tongchung-s)-s);
	else fo << (s%(s/2));
}

int main(){
	nhap();
	solve();
	fi.close();
	fo.close();
	return 0;
}
