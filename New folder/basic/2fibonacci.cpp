#include <bits/stdc++.h>

using namespace std;

int fibo(int n){
	
	int i,f1,f2,fi;
	
	if (n<=1) return n;
	else{
		f2=0; f1=1;
		for (i=2;i<=n;i++){
			fi=f1+f2;
			f2=f1;
			f1=fi;
		}
		return fi;
	}
	
}

int main(){
	
	int n,s;
	
	cout << "nhap n:"; cin >> n;
	
	s=(fibo(n-1)+fibo(n-2));
	
	cerr << s;
	
	return 0;
}
