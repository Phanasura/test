#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Order {
    int start;
    int end;
};

bool compare(Order a, Order b) {
    return a.end < b.end;
}

int main() {
    int n;
    cin >> n;

    vector<Order> orders(n);
    for (int i = 0; i < n; i++) {
        cin >> orders[i].start >> orders[i].end;
    }

    sort(orders.begin(), orders.end(), compare);

    int count = 0;
    int end = 0;
    for (int i = 0; i < n; i++) {
        if (orders[i].start >= end) {
            count++;
            end = orders[i].end;
        }
    }

    cout << count << endl;

    return 0;
}

