#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;
    int time;
public:
    Graph(int V);
    void addEdge(int u, int v);
    void findArticulationPointsAndBridges();
    void performTarjanDFS(int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<bool>& articulation, vector<pair<int, int>>& bridges);
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
    time = 0;
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void Graph::findArticulationPointsAndBridges() {
    vector<int> disc(V, -1);
    vector<int> low(V, -1);
    vector<int> parent(V, -1);
    vector<bool> articulation(V, false);
    vector<pair<int, int>> bridges;

    for (int i = 0; i < V; i++) {
        if (disc[i] == -1) {
            performTarjanDFS(i, disc, low, parent, articulation, bridges);
        }
    }

    cout << "Articulation Points: ";
    for (int i = 0; i < V; i++) {
        if (articulation[i]) {
            cout << i << " ";
        }
    }
    cout << endl;

    cout << "Bridges: ";
    for (const pair<int, int>& bridge : bridges) {
        cout << bridge.first << "-" << bridge.second << " ";
    }
    cout << endl;
}

void Graph::performTarjanDFS(int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<bool>& articulation, vector<pair<int, int>>& bridges) {
    static int time = 0;
    int children = 0;
    disc[u] = low[u] = ++time;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            children++;
            parent[v] = u;
            performTarjanDFS(v, disc, low, parent, articulation, bridges);
            low[u] = min(low[u], low[v]);

            if (low[v] > disc[u]) {
                bridges.push_back({u, v});
            }

            if (parent[u] == -1 && children > 1) {
                articulation[u] = true;
            }

            if (parent[u] != -1 && low[v] >= disc[u]) {
                articulation[u] = true;
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main() {
    Graph g(4);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.findArticulationPointsAndBridges();
    return 0;
}

