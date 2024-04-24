#include <bits/stdc++.h>

using namespace std;

ifstream fi("test.txt");

int sum,ans=0,a[1001],n,k;

void readin(){
    fi >> n >> k;
    for (int i=1;i<=n;i++) fi >> a[i];
}

void solve(){
    int j=1,i=1,res;
    while (j<=n){
        sum+=a[j];
        while (sum > k){
            
            
            sum-=a[i];
            i++;
            ans = max(ans,j-i+1);
        }
       // res=j-i+1;
        
        ++j;
    }
    cout << ans;
}
int main(){
    readin();
    solve();
    return 0;
    fi.close();
}