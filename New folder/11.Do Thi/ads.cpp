#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 2005;

vector<int> adj[MAXN];
int visited[MAXN];

void dfs(int u, int p) {
    visited[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
}

int main() {
    ifstream fi("test.txt");
    ofstream fo("kq.txt");

    int n, m;
    fi >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        fi >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int result = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, -1);
            result++;
        }
    }

    fo << result << endl;

    fi.close();
    fo.close();

    return 0;
}

