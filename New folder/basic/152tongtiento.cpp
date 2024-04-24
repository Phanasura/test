#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,a[1001],prefix[1001],l,r,kq,q;
void readin(){
    fi >> n;
    for (int i=1;i<=n;i++){
        fi >> a[i];
    }
    fi >> q;
}

void solve(){
    for (int i=1;i<=n;i++){
        prefix[i]=prefix[i-1]+a[i];
    }
    if (l == 1) cout << prefix[r];
    else{
        kq = prefix[r] - prefix[l-1];
        cout <<kq << endl; 
    } 
    
}
int main(){
	readin();
    prefix[0]=0;
    while (q--){
        fi >> l >> r;
        solve();
    }
    return 0;
    fi.close();
}
