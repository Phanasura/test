#include <bits/stdc++.h>
using namespace std;

const int maxn = 1001;
int n,m;
vector<pair<int, int> > adj[maxn];
bool used[maxn];
//int parent[maxn], d[maxn];

struct canh{
	int x,y,w;
};
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		//freopen((name + ".out").c_str(), "w", stdout);
	}
}

void readin(){
    cin >> n >> m;
	for (int i=0;i<m;i++){
		int x,y,w;
		cin >> x >> y  >> w;
		adj[x].push_back({y,w});
		adj[y].push_back({x,w});
	}	
	memset(used, false, sizeof(used));
//	for (int i=1;i<= n;i++) d[i] = INT_MAX;
}
void prim_dt(int u){
	priority_queue<pair<int, int>, vector<pair<int,int> >, greater<pair<int,int> > > Q;
	vector<canh> MST;
	int res = 0;
	Q.push({0,u});
	while (!Q.empty()){
		pair<int, int> top=Q.top();
		Q.pop();
		int dinh = top.second, trongso = top.first;
		if (used[dinh]) continue;
		res += trongso;
		used[dinh] = true;
//		if (u!= dinh){
//			MST.push_back({dinh, parent[dinh], trongso});
//		}
		for (auto it : adj[dinh]){
			int y = it.first, w = it.second;
			if (!used[y]){
				Q.push({w,y});
				
			}
//			if (!used[y] && w < d[y]){
//				Q.push({w,y});
//				d[y] = w;
//				parent[y] = dinh;
//			}
		}
	}
	cout << res << endl;
//	for (auto it:MST){
//		cout << it.x << " " << it.y << " " << it.w << endl;
//	}
}

void prim_normal(int u){
	vector <canh> MST; //cay khung
	int d = 0; //chieu dai cay khung
	used[u] = true; // dua dinh u vao tap V(MST)
	while (MST.size() < n-1){
		// e = (x,y) canh ngan nhat co x thuoc V va y thuoc V(MST)
		int min_w = INT_MAX;
		int X,Y;
		for (int i=1;i<=n;i++){
			if (used[i]){
				for (pair<int, int> it : adj[i]){
					int j = it.first, trongso = it.second;
					if (!used[j] && trongso < min_w){
						min_w = trongso;
						X = j;
						Y = i;
					}
				}
			}
		}
		MST.push_back({X,Y,min_w});
		d+=min_w;
		used[X] = true;
	}
	cout << d << endl;
	for (canh e : MST){
		cout << e.x << " " << e.y << " " << e.w << endl;
	}
}

int main(){
	setIO("Zerozone");
	readin();
	//cout << n << m;
	prim_dt(1);
	return 0;	
}
