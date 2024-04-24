#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long S;
    cin >> n >> S;

    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int left = 1, right = 1;
    long long sum = a[1];
    int count = 0;

    while (right <= n) {
        if (abs(sum) > S) {
            count += n - right + 1; 
            sum -= a[left];
            left++;
        } else {
            right++;
            sum += a[right];
        }
    }

    cout << count << endl;
    return 0;
}

