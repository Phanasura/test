#include <iostream>
#include <stack>
#include <string>

using namespace std;

const int MAX_N = 2500;
const int r_change[]{0, 1, 0, -1};
const int c_change[]{1, 0, -1, 0};
int rn;
int cn;
string building[MAX_N];
bool visited[MAX_N][MAX_N];

void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

void floodfill(int r, int c) {
	stack<pair<int, int> > frontier;
	frontier.push({r, c});
	while (!frontier.empty()) {
		r = frontier.top().first;
		c = frontier.top().second;
		frontier.pop();

		if (r < 0 || r >= rn || c < 0 || c >= cn ||
		    building[r][c] == '#' || visited[r][c])
			continue;

		visited[r][c] = true;
		for (int i = 0; i < 4; i++) {
			frontier.push({r + r_change[i], c + c_change[i]});
		}
	}
}

int main() {
	setIO("CROOMS");
	cin >> rn >> cn;
	for (int i = 0; i < rn; i++) { cin >> building[i]; }
	int room_num = 0;
	for (int i = 0;i < rn;i++) {
		for (int j = 0;j < cn;j++) {
			if (building[i][j]== '.' && !visited[i][j]) {
				floodfill(i, j);
				room_num++;
			}
		}
	}
	cout << room_num << endl;
}
