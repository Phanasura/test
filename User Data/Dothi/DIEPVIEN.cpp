#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAX = 105;
const int INF = 1e9;
int m, n, i1, j1, i2, j2, k;
bool grid[MAX][MAX];
bool visited[MAX][MAX];
int dist[MAX][MAX];
pair<int, int> parent[MAX][MAX];
int di[] = {-1,0,1, 0};
int dj[] = {0,1,0, -1};
char dir[] = {'U', 'R', 'D', 'L'};

bool ok(int x, int y) {
    return x >= 0 && x <= m && y >= 0 && y <= n && !grid[x][y];
}
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}
void printp() {
    vector<pair<int, int>> path;
    int x = i2, y = j2;
    while (x != i1 || y != j1) {
        path.push_back({x, y});
        pair<int, int> p = parent[x][y];
        x = p.first;
        y = p.second;
    }
    path.push_back({i1, j1});
    //cout << path.size() - 1 << endl;
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i].first << " " << path[i].second << endl;
    }
}

void bfs() {
    queue<pair<int, int>> q;
    q.push({i1, j1});
    visited[i1][j1] = true;
    dist[i1][j1] = 0;
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        int x = cur.first, y = cur.second;
        for (int d = 0; d < 4; d++) {
            int nx = x + di[d];
            int ny = y + dj[d];
            if (ok(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
                //cout << nx << " " << ny << endl;
            }
        }
    }
}

int main() {
	setIO("DIEPVIEN");
    cin >> m >> n >> i1 >> j1 >> i2 >> j2;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        grid[x][y] = true;
    }
    //cout << "-------------------"<<endl;
    bfs();
    if (!visited[i2][j2]) {
        cout << "NO" << endl;
    } else {
        cout << dist[i2][j2] << endl;
        printp();
    }

    return 0;
}

