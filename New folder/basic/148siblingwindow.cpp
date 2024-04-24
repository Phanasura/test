#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,k,a[1001],sum=0,idx,dp[1001];
void readin(){
    fi >> n >> k;
    for (int i=1 ; i <=n ; i++) fi >> a[i];
}

void solve(){
   // cout << sum << endl;
    for (int i=1;i<=k;i++) sum=sum+a[i];
    int res = sum,idx =0;
    for (int i=k+1;i<n;i++){
        sum = sum - a[i-k]+ a[i];
        if (sum >res){
            res =sum;
            idx = i;
        }
    }
    cout << res << endl;
    for (int j=idx-k+1;j<=idx;j++){
    	cout << a[j]<< " ";
	}
   // cout << sum;
   /*int res;
    for (int i=1;i<=n;i++){
        dp[i] = a[i];
        for (int j=1;j<i;j++){
            if (a[i] > a[j]) dp[i] = max(dp[i],dp[j]+a[i]);
            res= max(res,dp[i]);
        }
        
    }
    cout << res;*/
}

int main(){
    readin();
    solve();
    return 0;
    fi.close();
}

