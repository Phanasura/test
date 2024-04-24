#include <iostream>
#include <stack>
#include <string>

using namespace std;

const int MAX_N = 2500;
const int R_CHANGE[]{0, 1, 0, -1};
const int C_CHANGE[]{1, 0, -1, 0};

int row_num;
int col_num;
string building[MAX_N];
bool visited[MAX_N][MAX_N];

void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		//freopen((name + ".out").c_str(), "w", stdout);
	}
}

void floodfill(int r, int c) {
	stack<pair<int, int> > frontier;
	frontier.push({r, c});
	while (!frontier.empty()) {
		r = frontier.top().first;
		c = frontier.top().second;
		frontier.pop();

		if (r < 0 || r >= row_num || c < 0 || c >= col_num ||
		    building[r][c] == '#' || visited[r][c])
			continue;

		visited[r][c] = true;
		for (int i = 0; i < 4; i++) {
			frontier.push({r + R_CHANGE[i], c + C_CHANGE[i]});
		}
	}
}

int main() {
	setIO("test");
	cin >> row_num >> col_num;
	for (int i = 0; i < row_num; i++) { cin >> building[i]; }

	int room_num = 0;
	for (int i = 0; i < row_num; i++) {
		for (int j = 0; j < col_num; j++) {
			if (building[i][j] == '.' && !visited[i][j]) {
				floodfill(i, j);
				room_num++;
			}
		}
	}
	cout << room_num << endl;
}
