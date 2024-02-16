#include <bits/stdc++.h>
using namespace std;

const int maxn = 10000;
int zero[maxn][maxn];
bool visited[maxn][maxn];
const int r_new[]{0,1,0, -1};
const int c_new[]{1,0, -1,0};
int m,n;


void setIO(string name= "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  
	cout.tie(0);
	if (!name.empty()) {
		freopen((name+ ".inp").c_str(),"r", stdin); 
		freopen((name + ".out").c_str(),"w", stdout);
	}
}

void floodfill(int r, int c) {
	stack<pair<int, int> > frontier;
	frontier.push({r, c});
	while (!frontier.empty()) {
		r = frontier.top().first;
		c = frontier.top().second;
		frontier.pop();
		if (r < 0 || r >= m || c < 0 || c >= n || zero[r][c] == 1 || visited[r][c])
			continue;
		visited[r][c] = true;
		for (int i = 0;i<4;i++) {
			frontier.push({r+r_new[i], c+c_new[i]});
		}
	}
}

int main() {
	setIO("Zerozone");
	cin >> m >> n;
    for (int i=0;i<m;i++){
    	for (int j=0;j<n;j++){
    		cin >> zero[i][j];
		}
	}
	int num = 0;
	for (int i = 0;i < m;i++) {
		for (int j = 0;j < n;j++) {
			if (zero[i][j] == 0 && !visited[i][j]) {
				floodfill(i, j);
				num++;
			}
		}
	}
	cout << num << endl;
//	for (int i=0;i<m;i++){
//    	for (int j=0;j<n;j++){
//    		cout << zero[i][j];
//		}
//		cout << endl;
//	}
    
	return 0;
}
