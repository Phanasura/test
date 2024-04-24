#include <bits/stdc++.h>
using namespace std;
int a,b,c,i;
bool z;
int kiemtranguyento(int n){
	if (n<2) return 0;
	for (int i=2;i<=sqrt(n);i++)
	    if (n%i==0)
	      return 0;
	return -1;
}
void nhap(int &a,int &b){
	freopen(".inp",r,stdin);
	cin>>a>>b;
}
void xuat(int a,int b){
	freopen(".out","w",stdout);
	cout <<a<<" "<<b;
}
void xuly(int a,int b){
	freopen(".inp","w",stdout);
	z=true;
	if ((a%2==0)&&(b%2!=0)) || ((a%2!=0)&&(b%2==0))
	{
		cout <<a<<"va"<<b<<"khong la so nguyen to tuong duong";
		z=false;
	}
	else
	{
		if (a>=b)
		c=a;
		else
		c=b;
		for (i=1;i<c/2;i++)
		if (kiemtranguyento(i)==1)
		if 	  ((a%2==0)&&(b%2!=0)) || ((a%2!=0)&&(b%2==0))
		{
			cout << a<<"va"<<b<<"khong la so nguyen to tuong duong"
			z=false;
			break;
		}
	}
	if (z==true)
	  cout << a<< "va"<<b<< "la so nguyen to tuong duong";
}
int main(){
	nhap(a,b);
	xuly(a,b);
	return 0;
}
