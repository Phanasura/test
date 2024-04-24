#include <iostream>
using namespace std;

const int mod = 998244353;

int main() {
    int n;
    cin >> n;

    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x = a[i], y = a[j];
            int d = 0;
            while (x > 0 || y > 0) {
                if (x % 10 != y % 10) {
                    d++;
                }
                x /= 10;
                y /= 10;
            }
            ans = (ans + d) % mod;
        }
    }

    cout << ans << endl;
    return 0;
}

