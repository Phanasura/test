#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXX = 1e6 + 5;
int n, x, c[MAXN], f[MAXX];

void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

void readin(){
	cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
}

void solve(){
	memset(f, -1, sizeof(f));
    f[0] = 0;
    for (int i =1;i<= n;i++) {
        for (int j = c[i];j<= x; j++) {
            if (f[j - c[i]] != -1) {
                if (f[j] == -1 || f[j] > f[j - c[i]] + 1) {
                    f[j] = f[j - c[i]] + 1;
                }
            }
        }
    }

    cout << f[x] << '\n';
}

int main(){
	setIO("doitien3");
	readin();
	solve();
	return 0;
}
