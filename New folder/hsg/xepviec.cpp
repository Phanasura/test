#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 105;
const int MAXK = 105;
const int MAXS = (1 << 16) + 5;

int k, n;
int v[MAXK][MAXN];
int f[MAXK][MAXS];

int main() {
    scanf("%d%d", &k, &n);
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &v[i][j]);
        }
    }

    memset(f, -0x3f, sizeof(f));
    f[0][0] = 0;

    for (int i = 1; i <= k; i++) {
        for (int S = 0; S < (1 << n); S++) {
            for (int T = S; T >= 0; T = (T - 1) & S) {
                int sum = 0;
                for (int j = 1; j <= n; j++) {
                    if (T & (1 << (j - 1))) {
                        sum += v[i][j];
                    }
                }
                f[i][S] = max(f[i][S], f[i - 1][S - T] + sum);
            }
        }
    }

    printf("%d\n", f[k][(1 << n) - 1]);

    return 0;
}

