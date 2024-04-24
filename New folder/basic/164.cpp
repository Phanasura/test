#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1001;

int N, K;
int prefixSum[MAXN][MAXN];

int main() {
    cin >> N >> K;

    // Compute the prefix sum of the number of coats of paint for each point.
    // If a point has K coats of paint, mark it as 1. Otherwise, mark it as 0.
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        prefixSum[x1][y1]++;
        prefixSum[x2][y2]++;
        prefixSum[x1][y2]--;
        prefixSum[x2][y1]--;
    }

    // Compute the actual number of coats of paint for each point.
    // This is done by computing the prefix sum along the rows and then along the columns.
    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= 1000; j++) {
            prefixSum[i][j] += prefixSum[i-1][j] + prefixSum[i][j-1] - prefixSum[i-1][j-1];
        }
    }

    // Count the number of points with exactly K coats of paint.
    int ans = 0;
    for (int i = 0; i <= 1000; i++) {
        for (int j = 0; j <= 1000; j++) {
            if (prefixSum[i][j] == K) {
                ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
