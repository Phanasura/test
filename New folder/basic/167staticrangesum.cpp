#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,a[1001],prefix[1001],l,r,kq,q;
void readin(){
    cin >> n >> q;
    for (int i=1;i<=n;i++){
        cin >> a[i];
    }
}

void solve(){
    
    
    if (l == 1 || l == 0) cout << prefix[r];
    else{
        kq = prefix[r] - prefix[l];
        cout <<kq << endl; 
    } 
    
}
int main(){
	readin();
    prefix[0]=0;
    for (int i=1;i<=n;i++){
        prefix[i]=prefix[i-1]+a[i];
    }
    for (int i=1;i<=n;i++){
        cout << prefix[i]<< " ";
    }
    cout << endl;
    while (q--){
        cin >> l >> r;
        solve();
    }
    return 0;
    fi.close();
}
