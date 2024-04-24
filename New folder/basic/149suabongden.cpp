#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int x,n,k,b,a[1001],cnt,ans;
void readin(){
    fi >> n >> k  >> b;
    for (int i=1;i<=b;i++){
        fi >> x;
        a[x]=1;
    }
}
void solve(){
    for (int i=1;i<=k;i++){
        if (a[i]==1){
            cnt=cnt+1;
        }
    }
    ans = cnt;
    for (int i=k+1;i<=n;i++){
        cnt = cnt -a[i-k]+a[i];
        ans = min(ans,cnt);
    }
    cout << ans ;
}
int main(){
    readin();
    solve();
    return 0;
    fi.close();
}