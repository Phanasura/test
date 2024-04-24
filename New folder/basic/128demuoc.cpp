#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");

int n,a[1001],prefix[1001],q,r,l;
void readin(){
    fi >> n;
    prefix[0]=0;
    for (int i=1;i<=n;i++){
    	fi>> a[i];
    	
	}
	fi >> q;
}
/*
1 3 4 7 6 12 8 15 13
1 2 2 3 2 4 2 4 3
*/
int countuoc(int x){
	int d=2;
    for (int i=2;i<=sqrt(x);i++){
        if (x%i==0) d+=2;
    }
    if (sqrt(x) == int(sqrt(x))) d--;
    return d;
}
void solve(){
    int kq;
    for (int i=1;i<=n;i++){
    	prefix[i]=prefix[i-1]+ countuoc(a[i]);
	}
	kq = prefix[r] - prefix[l-1];
	cout << kq<< endl;
}
int main(){
    readin();
    while (q--){
        fi >> l >> r;
		solve();
	}
    return 0;
    fi.close();
}
