#include <iostream>
#include <algorithm>
using namespace std;

long long solve(long long a, long long b, long long c) {
    long long pos[3] = {a, b, c};
    sort(pos, pos + 3)
    long long dist12 = pos[1] - pos[0];
    long long dist13 = pos[2] - pos[0];
    long long dist23 = pos[2] - pos[1];
    if (dist12 == 0 && dist13 == 0) {
        return 0;
    }
    if (dist12 == 0 || dist13 == 0 || dist23 == 0) {
        return 1;
    }
    if (dist12 > 2 || dist13 > 2 || dist23 > 2) {
        return 2;
    }
    if (dist12 == 2 || dist13 == 2 || dist23 == 2) {
        return 1;
    }
    return 0;
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        long long a, b, c;
        cin >> a >> b >> c;
        cout << solve(a, b, c) << endl;
    }

    return 0;
}

