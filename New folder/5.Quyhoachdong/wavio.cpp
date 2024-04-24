#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
int n;
int a[MAXN], L[MAXN], R[MAXN];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        L[i] = R[i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (a[i] > a[j]) {
                L[i] = max(L[i], L[j] + 1);
            }
        }
    }
    for (int i = n-1; i >= 1; i--) {
        for (int j = n; j > i; j--) {
            if (a[i] > a[j]) {
                R[i] = max(R[i], R[j] + 1);
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, min(L[i], R[i]));
    }
    cout << 2*res-1 << endl;
    return 0;
}
