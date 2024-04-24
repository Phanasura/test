#include <bits/stdc++.h>
using namespace std;

const int N = 10;
int n, k, a[N+5], s[N+5];
bool vis[N+5];
ifstream fi("KSUBSET.INP");
ofstream fo("KSUBSET.OUT");
bool solve(int vt, int sumht, int dem) {
    if (dem == k) return true;
    if (sumht == s[dem]) return solve(0, 0, dem+1);
    if (sumht > s[dem]) return false;
    for (int i = vt; i < n; i++) {
        if (vis[i]) continue;
        vis[i] = true;
        if (solve(i+1,sumht+a[i], dem)) return true;
        vis[i] = false;
    }
    return false;
}

int main() {
    fi >> n >> k;
    for (int i = 0; i < n; i++) {
        fi >> a[i];
    }
    for (int i = 0; i < k; i++) {
        fi >> s[i];
    }
    if (solve(0, 0, 0)) fo << "YES"<< endl;
    else fo << "NO" << endl;
    return 0;
}
