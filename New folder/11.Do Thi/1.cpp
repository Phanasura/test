#include <iostream>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    cout << (a / b - ((a < 0 && b > 0) || (a > 0 && b < 0))) << endl;
    return 0;
}

