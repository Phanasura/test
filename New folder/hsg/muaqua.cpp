#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 25;

int k, n, s;
ll f[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> k >> n >> s;
    vector<vector<int>> d(n+1, vector<int>(k+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            cin >> d[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (d[i][j] > s) continue;
            for (int t = k; t >= j; t--) {
                for (int p = 1; p <= s-d[i][j]; p++) {
                    f[t][p+d[i][j]] = max(f[t][p+d[i][j]], f[t-1][p] + d[i][j]);
                }
            }
        }
    }
    if (f[k][s] == 0) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        vector<int> res(k+1);
        int j = s;
        for (int i = k; i >= 1; i--) {
            for (int t = j; t >= 1; t--) {
                if (f[i][t] == f[i-1][j-t+d[n][i]]) {
                    res[i] = j-t+d[n][i];
                    j = t-1;
                    break;
                }
            }
        }
        for (int i = 1; i <= k; i++) {
            cout << res[i] << " ";
        }
    }
    return 0;
}

