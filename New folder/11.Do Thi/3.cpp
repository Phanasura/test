#include <iostream>
#include <vector>

using namespace std;

vector<int> parent;
vector<int> size;

int find(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find(parent[v]);
}

void union_sets(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    parent.resize(n + 1);
    size.resize(n + 1, 1);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        union_sets(u, v);
    }

    int num_components = 0;
    for (int i = 1; i <= n; i++) {
        if (find(i) == i) {
            num_components++;
        }
    }

    cout << num_components << endl;

    if (find(1) == find(n)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}

