#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 5;

int n, k, r, t;
int camera[MAXN];
int cnt[MAXN];

void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

void readin(){
	cin >> n >> k >> r >> t;
    for (int i = 1; i <= k; i++) {
        cin >> camera[i];
    }
    sort(camera+1, camera+k+1);	
}

void solve(){
	int j = 1;
    for (int i = 1; i <= n-r+1; i++) {
        while (j <= k && camera[j] <i) j++;
        cnt[i] = cnt[i-1] -(j-1 >= 1 && camera[j-1] <= i-r ? 1 : 0) + (j <= k && camera[j] <= i+r-1 ? 1 : 0);
    }

    int ans = 0;
    vector<int> res;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] < t) { 
            ans++; 
            res.push_back(i);
            
            cnt[i]++; cnt[i+1]++; cnt[i+r]--;
            cnt[max(i-r+1, 1)]--; cnt[max(i-r+1, 1)-1]--;
        }
    }

    cout << ans << '\n';
    for (int x=0 ;x<res.size();x++) {
        cout << res[x] << ' ';
    }
}

int main(){
	//setIO("Camera");
	readin();
	solve();
	return 0;
}


