#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;
int n, p;
int a[MAXN];
bool used[MAXN];
int cnt = 0;

void backtrack(int pos) {
    if (pos > n) {
        cnt++;
        if (cnt == p) {
            for (int i = 1; i <= n; i++) {
                cout << a[i] << " ";
            }
            exit(0);
        }
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;
            a[pos] = i;
            backtrack(pos + 1);
            used[i] = false;
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> p;
    sort(a + 1, a + n + 1);
    backtrack(1);
    return 0;
}
