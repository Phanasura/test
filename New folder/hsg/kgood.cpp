#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
long long a[100001],f[1000001],n,k,i,j,res,t,vt;
void readin(){
	fi>>n>>k;
    for (i=1;i<=n;i++) 
	fi>>a[i];
}

void solve(){ i=1;
    for (j=1;j<=n;j++) {
        f[a[j]]++;
        if (f[a[j]]==1) t++;
        if (t>k) {
            f[a[i]]--; if (f[a[i]]==0) t--;
            i++;
        }
        if (j-i+1>res) {res=j-i+1; vt=i;}
    }
}
int main(){
    readin();
    solve();
    fo<<vt<<" "<<vt+t-1;
}
