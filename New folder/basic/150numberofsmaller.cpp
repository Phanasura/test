#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,m,a[1001],b[1001];
void readin(){
    fi >> n >> m;
    for (int i=1;i<=n;i++) fi >> a[i];
    for (int i=1;i<=m;i++) fi >> b[i];
}

void solve(){
    int i=1,j=1;
    while (i<=n && j<=m){
        if (a[i]<b[j]) {
            i=i+1;
            //j=j+1;
           // cout << i << " ";
        }
        else{
            ++j;
            cout << i-1 << " ";
        }
    }
    while (j <=m){
        cout << n << " ";
        ++j;
    }
}
int main(){
    readin();
    solve();
    return 0;
    fi.close();
}