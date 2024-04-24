#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    sort(s.begin(), s.end(), greater<int>());

    int ans = 0;
    int i = 0, j = n - 1;
    while (i <= j) {
        ans++;
        if (i == j) {
            i++;
        } else if (s[i] + s[j] <= x) {
        	cout << " " << s[i] << " " << s[j];
            i++;
            j--;
        } else {
            i++;
        }
    }

    cout << ans << endl;

    return 0;
}

