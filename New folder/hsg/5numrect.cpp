#include <bits/stdc++.h>
#define file "numrect"

typedef long long ll;
using namespace std;
int svb(int a){
	int s;
	for (int i=1;i<=a;i++){
		s+=i*i;
	}
	return s;
	
}
int svkb(int n,int m){
	int s=0;
	int i=n,j=m;
	while ((i>=1)||(j>=1)){
		s+=i*j;
		i--;
		j--;	
	cout <<s;
    }
}
int main()
{
   
    ll n,m,a,b,shcn,sv;
    cout << "\nnhap canh hinh cn:";
    cin >> n>>m;
    cout <<"\nnhap canh hinh vuong:";
    cin >> a>>b;
    shcn = (m*m-1*n*n-1)/4;
	if (a=b) sv=svb(a);
	else sv=svkb(a,b);
	cout << "dien tich hcn la:" << shcn<< endl;
	cout << "dien tich vuong la" << sv << endl;
}
