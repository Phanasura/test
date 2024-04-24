#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> adj[N]; 
bool infected[N]; 
int n, k;

void dfs(int u) {
    infected[u] = true;
    for (int v=0;v<adj[u].size();v++) {
        if (!infected[v]) {
            dfs(v);
        }
    }
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int m;
        cin >> m;
        while (m--) {
            int v;
            cin >> v;
            adj[i].push_back(v);
        }
    }

    dfs(k);

    int cnt = 0; 
    for (int i = 1; i <= n; i++) {
        if (infected[i]) {
            cnt++;
        }
    }
    cout << cnt << endl;

    for (int i = 1; i <= n; i++) {
        if (infected[i]) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}

