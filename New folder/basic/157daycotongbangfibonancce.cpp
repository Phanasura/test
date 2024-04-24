#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,f[1001];
void readin(){
    fi >> n;
    f[1]=1;
    f[2]=1;
    int i=3;
    while (f[i-1]+f[i-2]<=n){
    	f[i]=f[i-1]+f[i-2];
    	i+=1;
	}
	i-=1;
	while (n!=0){
		if (f[i]<=n){
			cout << f[i];
			n=n-f[i];
			if (n>0) cout << "+";
		}
		i-=1;
	}
	
}
int main(){
	readin();
	//solve();
	return 0;
	fi.close();
}
