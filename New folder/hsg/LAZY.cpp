#include <bits/stdc++.h>
using namespace std;
const int N = 2e6+5; 
int vt[N],tmp=0,ans=0,n,k,c[N],x[N],res,s[N];

void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

bool check(){
	return k>tmp;
}

void readin(){
	cin >> n >> k;
    for (int i = 1; i <= n; i++){
        cin >> c[i] >> x[i];
        vt[x[i]] = c[i];
        tmp = max(tmp,x[i]);
    }
}

void solve(){
	memset(s,0,sizeof(s));
	res = k*2+1;
    if (res >= tmp){
        for (int i=1;i<=n;i++){
        	ans = ans+c[i];
		}
    }
    else {
    	for (int i=1;i<=res;i++){
    		s[k+1] += vt[i];
		}
		if (ans < s[k+1]){
			ans = s[k+1];
		}
		int st=k+2,g=tmp-k;
        for (int i=st;i<=g;i++){
        	s[i] = s[i-1]-vt[i-k-1]+vt[i+k];
			ans = max(ans,s[i]);
		}
	}
    cout << ans;
}

int main(){
	setIO("LAZY");
	memset(vt,0,sizeof(vt));
	readin();
	solve();
	return 0;
}

