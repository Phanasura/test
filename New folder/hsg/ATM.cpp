#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n, s;
int t[MAXN + 5];
int ans[MAXN + 5];

bool solve(int i, int sum) {
    if (sum == s) {
        return true;
    }
    if (i > n || sum > s) {
        return false;
    }
    for (int j = i; j <= n; j++) {
        ans[j] = 1;
        if (solve(j + 1, sum + t[j])) {
            return true;
        }
        ans[j] = 0;
    }
    return false;
}

int main() {
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }
    if (solve(1, 0)) {
        for (int i = 1; i <= n; i++) {
            if (ans[i]) {
                cout << t[i] << " ";
            }
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}
