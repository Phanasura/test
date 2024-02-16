#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

vector<int> graph[MAXN];
int subtreeSize[MAXN];

int dfs(int node, int parent) {
    subtreeSize[node] = 1;
    for (int child : graph[node]) {
        if (child != parent) {
            subtreeSize[node] += dfs(child, node);
        }
    }
    return subtreeSize[node];
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, 0);

    vector<int> sizes;
    for (int i = 1; i <= n; ++i) {
        sizes.push_back(subtreeSize[i]);
    }

    sort(sizes.begin(), sizes.end());

    int result = sizes[n - 1] - sizes[0];
    cout << result << endl;

    return 0;
}

