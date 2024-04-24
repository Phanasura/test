#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    map<int, int> b;
    vector<int> used(n + 1, 0);
    int count = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        b[x] = i;
    }
    cout << count << endl;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        int j = b[x];
        if (j && !used[j]) {
            count++;
            used[j] = 1;
            cout << x << " ";
        }
    }

    
    return 0;
}
