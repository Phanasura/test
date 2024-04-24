#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n;
int a[N], f[N], tr[N];
//ifstream fi("test.txt");
ifstream fi("lis.inp");
ofstream fo("lis.out");

void readin(){
	fi >> n;
    for (int i = 1; i <= n; ++i) {
        fi >> a[i];
        f[i] = 1; 
    }
}

void solve(){
	int mx = 0, pos = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            if (a[j] < a[i] && f[j] + 1 > f[i]) {
                f[i] = f[j] + 1;
                tr[i] = j; 
            }
        }
        if (f[i] > mx) {
            mx = f[i];
            pos = i; 
        }
    }

    fo << mx << '\n';
    vector<int> res;
    while (pos > 0) {
        res.push_back(pos);
        pos = tr[pos]; 
    }
    reverse(res.begin(), res.end());
    for (int i=0;i<res.size();i++) {
        fo << res[i] << ' ';
    }
    fo << '\n';

}
int main() {
    ios::sync_with_stdio(false);
    readin();
    solve();
    fi.close();
    fo.close();
	return 0;
}
