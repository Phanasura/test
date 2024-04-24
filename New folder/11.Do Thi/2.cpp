#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n;
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
void in(){
	cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}
void solve(){
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = gcd(result, arr[i]);
    }
    if (result == 1) {
        cout << 0 << endl;
    } else {
        cout << -1 << endl;
    }
}
int main() {
    in();
    solve()

    return 0;
}

