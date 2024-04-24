#include<bits/stdc++.h>

using namespace std;

ifstream fi("caykhe.inp");
ofstream fo("caykhe.out");

long long n,m,x[10000],w[10000],v[10000],save[10000],maxx=0;

void nhap(){
	fi>>n>>m;
	for (int i=1;i<=n;i++){
		fi>>w[i]>>v[i];
	}
}
void xuat(){
	int mw=0,mv=0;
	for (int i=1;i<=n;i++){
		if (x[i]==0){
			mv+=v[i]; mw+=w[i];
		}
	}
	if ((maxx<mv) && (mw<=m)){
		maxx=mv;
		for (int i=1;i<=n;i++) save[i]=x[i];
	}		
}
void ckhe(int i){
	for (int j=0;j<=1;j++){ x[i]=j;
		if (i==n) xuat();
		else ckhe(i+1);
	}
}

int main(){
	nhap();
	ckhe(1);
	fo<<maxx<<endl;
	return 0;
	fi.close();
	fo.close();
}
