#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9;

int main() {
    int n;
    cin >> n;
    vector<int> a(n+1), s(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i-1] + a[i];
    }
    vector<int> dp(n+1);
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i-1];
        for (int j = i-1; j >= 0; j--) {
            if (a[i] < a[j]) {
                dp[i] = (dp[i] + (s[i-1]-s[j])-(i-j-1)*a[i]) % mod;
            }
        }
    }
    cout << (dp[n] % mod + mod) % mod << endl;
    return 0;
}

