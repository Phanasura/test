void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inP").c_str(), "r", stdin); 
		//freopen((name + ".out").c_str(), "w", stdout);
	}
}
<!--
////LISTED:
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; ++i) {
        pq.push(nums[i]);
        priority_queue<int, vector<int>, greater<int>> tmp_pq = pq;
        while (!tmp_pq.empty()) {
            cout << tmp_pq.top();
            tmp_pq.pop();
            if (!tmp_pq.empty()) cout << " ";
        }
        cout << endl;
    }

    return 0;
}






////QMIN
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int INF = 1e9 + 7;

struct Node {
    int min_val;
};

class SegmentTree {
private:
    vector<Node> st;
    int size;

    int left(int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }

    void build(vector<int> &arr, int p, int L, int R) {
        if (L == R) {
            st[p].min_val = arr[L];
        } else {
            int mid = (L + R) / 2;
            build(arr, left(p), L, mid);
            build(arr, right(p), mid + 1, R);
            st[p].min_val = min(st[left(p)].min_val, st[right(p)].min_val);
        }
    }

    int query(int p, int L, int R, int i, int j) {
        if (i > R || j < L) return INF;
        if (L >= i && R <= j) return st[p].min_val;
        int mid = (L + R) / 2;
        int p1 = query(left(p), L, mid, i, j);
        int p2 = query(right(p), mid + 1, R, i, j);
        return min(p1, p2);
    }

public:
    SegmentTree(vector<int> &arr) {
        size = arr.size();
        st.resize(4 * size);
        build(arr, 1, 0, size - 1);
    }

    int query(int i, int j) {
        return query(1, 0, size - 1, i, j);
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    SegmentTree st(arr);

    for (int q = 0; q < m; ++q) {
        int p, r;
        cin >> p >> r;
        cout << st.query(p - 1, r - 1) << endl;
    }

    return 0;
}














////Segment Tree
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int INF = 1e9 + 7;

struct Node {
    int max_val;
};

class SegmentTree {
private:
    vector<Node> st;
    int size;
    
    int left(int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }

    void build(vector<int> &arr, int p, int L, int R) {
        if (L == R) {
            st[p].max_val = arr[L];
        } else {
            int mid = (L + R) / 2;
            build(arr, left(p), L, mid);
            build(arr, right(p), mid + 1, R);
            st[p].max_val = max(st[left(p)].max_val, st[right(p)].max_val);
        }
    }

    int query(int p, int L, int R, int i, int j) {
        if (i > R || j < L) return -INF;
        if (L >= i && R <= j) return st[p].max_val;
        int mid = (L + R) / 2;
        int p1 = query(left(p), L, mid, i, j);
        int p2 = query(right(p), mid + 1, R, i, j);
        return max(p1, p2);
    }

    void update(int p, int L, int R, int idx, int new_val) {
        if (L == R && L == idx) {
            st[p].max_val = new_val;
        } else if (idx >= L && idx <= R) {
            int mid = (L + R) / 2;
            update(left(p), L, mid, idx, new_val);
            update(right(p), mid + 1, R, idx, new_val);
            st[p].max_val = max(st[left(p)].max_val, st[right(p)].max_val);
        }
    }

public:
    SegmentTree(vector<int> &arr) {
        size = arr.size();
        st.resize(4 * size);
        build(arr, 1, 0, size - 1);
    }

    int query(int i, int j) {
        return query(1, 0, size - 1, i, j);
    }

    void update(int idx, int new_val) {
        update(1, 0, size - 1, idx, new_val);
    }
};

int main() {
    int n, Q;
    cin >> n >> Q;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    SegmentTree st(arr);

    for (int q = 0; q < Q; ++q) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 1) {
            st.update(u - 1, v);
        } else if (type == 2) {
            cout << st.query(u - 1, v - 1) << " ";
        }
    }

    return 0;
}








	
//QSUM 
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, Q;
    cin >> n >> Q;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    vector<int> prefix_sum(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + arr[i - 1];
    }
    
    for (int q = 0; q < Q; ++q) {
        int type;
        cin >> type;
        
        if (type == 1) {
            int i, x;
            cin >> i >> x;
            arr[i - 1] += x;
            for (int j = i; j <= n; ++j) {
                prefix_sum[j] += x;
            }
        } else if (type == 2) {
            int u, v;
            cin >> u >> v;
            cout << prefix_sum[v] - prefix_sum[u - 1] << " ";
        }
    }
    
    return 0;
}














//////Stack
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Hàm bi?u di?n s? nguyên duong n du?i d?ng nh? phân
string binaryRepresentation(unsigned long long n) {
    if (n == 0) return "0"; // Tru?ng h?p d?c bi?t khi n = 0

    stack<char> binDigits;
    while (n > 0) {
        char digit = (n % 2) + '0'; // Chuy?n du thành ký t? '0' ho?c '1'
        binDigits.push(digit);
        n /= 2;
    }

    string binary;
    while (!binDigits.empty()) {
        binary += binDigits.top();
        binDigits.pop();
    }

    return binary;
}

// Hàm chuy?n d?i s? nguyên duong n sang h? co s? 16
string hexadecimalRepresentation(unsigned long long n) {
    if (n == 0) return "0"; // Tru?ng h?p d?c bi?t khi n = 0

    stack<char> hexDigits;
    while (n > 0) {
        int remainder = n % 16;
        char digit;
        if (remainder < 10) {
            digit = remainder + '0'; // Ch? s? t? 0 d?n 9
        } else {
            digit = remainder - 10 + 'A'; // Ch? s? t? A d?n F
        }
        hexDigits.push(digit);
        n /= 16;
    }

    string hexadecimal;
    while (!hexDigits.empty()) {
        hexadecimal += hexDigits.top();
        hexDigits.pop();
    }

    return hexadecimal;
}

int main() {
    // Bi?u di?n s? nguyên duong n du?i d?ng nh? phân
    unsigned long long n;
    cin >> n;
    string binary = binaryRepresentation(n);
    cout << "Bi?u di?n nh? phân c?a " << n << ": " << binary << endl;

    // Chuy?n d?i s? nguyên duong n sang h? co s? 16
    string hexadecimal = hexadecimalRepresentation(n);
    cout << "S? " << n << " chuy?n sang h? th?p l?c phân: " << hexadecimal << endl;

    return 0;
}

#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Hàm ki?m tra dãy ngo?c dúng
bool isValid(const string& s) {
    stack<char> stk;

    for (char c : s) {
        if (c == '(') {
            stk.push(c);
        } else if (c == ')') {
            if (stk.empty()) {
                return false; // N?u g?p d?u ')' mà stack r?ng, không dúng
            }
            stk.pop();
        }
    }

    return stk.empty(); // N?u stack không r?ng sau khi xét h?t, là dãy ngo?c dúng
}

int main() {
    string s;
    cin >> s;

    if (isValid(s)) {
        cout << "yes";
    } else {
        cout << "no";
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int N;
    cin >> N;

    priority_queue<int, vector<int>, greater<int>> pq; // Hàng d?i uu tiên s?p x?p tang d?n
    //priority_queue<int, vector<int>, less<int>> pq;

    long long total_cost = 0; // T?ng chi phí

    // Ð?c d? dài các mi?ng g? vào hàng d?i uu tiên
    for (int i = 0; i < N; ++i) {
        int length;
        cin >> length;
        pq.push(length);
    }

    // C?t mi?ng g?
    while (pq.size() > 1) {
        int piece1 = pq.top();
        pq.pop();
        int piece2 = pq.top();
        pq.pop();
        int combined_piece = piece1 + piece2;
        total_cost += combined_piece;
        pq.push(combined_piece);
    }

    cout << total_cost;

    return 0;
}
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}




	
//Tinh khoi luong nguyen tu
#include <iostream>
#include <string>
#include <stack>
#include <map>

using namespace std;

map<char, int> atomic_mass = {
    {'C', 12},
    {'H', 1},
    {'O', 16}
};

int calculate_molecular_mass(string formula) {
    stack<int> s;
    int mass = 0;
    
    for (char &c : formula) {
        if (c == '(') {
            s.push(-1); // Ðánh d?u m? ngo?c
        } else if (c == ')') {
            int sum = 0;
            while (s.top() != -1) {
                sum += s.top();
                s.pop();
            }
            s.pop(); // Lo?i b? d?u -1
            s.push(sum);
        } else if (isdigit(c)) {
            int count = c - '0';
            int top = s.top();
            s.pop();
            s.push(top * count);
        } else {
            s.push(atomic_mass[c]);
        }
    }
    
    while (!s.empty()) {
        mass += s.top();
        s.pop();
    }
    
    return mass;
}

int main() {
    int T;
    cin >> T;
    
    for (int i = 0; i < T; ++i) {
        string formula;
        cin >> formula;
        cout << calculate_molecular_mass(formula) << endl;
    }
    
    return 0;
}














///CÂY KHUng

//DSU
#include<bits/stdc++.h>
#define ll long long
#define codespeed ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;
struct edge{
	int u,v;
	int w;
};
const int maxn = 1001;
int n, m;
int parent[maxn], sz[maxn];
vector<edge> canh;

void makeset(){
	for(int i = 1; i <= n; i++){
		parent[i] = i;
		sz[i] = 1;
	}
}
int find(int v){
	if(v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}
bool Union(int a, int b){
	a = find(a);
	b = find(b);
	if (a==b) return false;
	if (sz[a] < sz[b]) swap(a, b);
	parent[b] = a;
	sz[a] + sz[b];
	return true;
}
void inp(){
	cin>>n>>m;
	for(int i = 0; i<m; i++){
		int x,y,w;
		cin>>x>>y>>w;
		edge e;
		e.u = x; e.v = y; e.w = w;
		canh.push_back(e);
	}
}
bool cmp(edge a, edge b){
	return a.w < b.w;
}
void kruskal(){
	vector<edge> mst;
	int d = 0;
	sort(canh.begin(), canh.end(), cmp);
	for(int i = 0; i < m; i++){
		if(mst.size() == n - 1) break;
		edge e = canh[i];
		if(Union(e.u, e.v)){
			mst.push_back(e);
			d += e.w;
		}
	}
	if(mst.size()!= n - 1){
		cout<<"ko lien thong";
	}else{
		cout<<d<<endl;
		for(auto it:mst){
			cout<<it.u<<" "<<it.v<<" "<<it.w<<endl;
		}
	}
}
int main(){
    codespeed
//    freopen("djoinset.inp","r",stdin);
//    freopen("djoinset.out","w",stdout);
	inp();
	makeset();
	kruskal();
return 0;
}





//ATTACK
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll nmax = 1e5+5;
ll n,m, c[nmax];
struct Edge{
    ll u,v,w;
} e[nmax];
struct DSU{
    ll par[nmax];
    void init(ll n){
        for(int i =1; i<=n; i++) par[i] = i;
    }
    ll find(ll u){
        if (par[u] == u) return u;
        return par[u] = find(par[u]);
    }
    bool join(ll u, ll v){
        u = find(u); v = find(v);
        if (u == v) return false;
        par[v] = u;
        return true;
    }
} dsu;
bool cmp(Edge a, Edge b){
    return a.w>b.w;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("attack.inp", "r", stdin);
    freopen("attack.out", "w", stdout);
    cin>>n>>m;
    dsu.init(n);
    ll sum = 0;
    for(int i = 1; i<=n; i++) cin>>c[i];
    for(int i = 1; i<=m; i++){
        ll x,y;
        cin>>x>>y;
        e[i] = {y,x,c[x]+c[y]};
        sum+=c[x]+c[y];
    }
    sort(e+1,e+m+1,cmp);
    ll ans = 0;
    for(int i = 1; i<=m; i++){
        if (!dsu.join(e[i].u, e[i].v)) continue;
        ans+=e[i].w;
    }
    cout<<sum-ans;
    return 0;
}



//QBMST
#include<bits/stdc++.h>
using namespace std;
const int MaxN = 1 + 1e5;
typedef long long ll;
int n, m, parent[MaxN];

void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

class Edge {
    public:
        int u, v, w;
        Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {}
        bool operator < (const Edge &op) const {
            return w < op.w;
        }
};
vector<Edge> edges;

void readin(){
	cin >> n >> m;
    for(int i = 0 ; i < m ; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(Edge(u, v, w));
    }
}

int find_set(int u){
    if(u == parent[u]) return u;
    return parent[u] = find_set(parent[u]);
}

void make_set(int u){
    parent[u] = u;
}

void pre_data(){
	for(int i = 1 ; i <= n ; ++i) make_set(i);
    sort(edges.begin(), edges.end());
}

void kruskal(){
	ll ans = 0;
    for(int i = 0 ; i < m ; ++i){
        Edge e = edges[i];
        int u = find_set(e.u);
        int v = find_set(e.v);
        if(u != v){
            ans += e.w;
            parent[u] = v;
        }
    }
    cout << ans;
}

int main(){
	setIO("QBMST");
    readin();
    pre_data();
    kruskal();
    return 0;
}






#include <bits/stdc++.h>
using namespace std;
//ifstream fi("test.txt");
//ofstream fo("kq.txt"); 
int n,m,s,t,y,x,w;
const int maxn = 100001;
vector <pair<int,int> > adj[maxn];
int pre[maxn];
const int inf = 1e6;
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}
void readin(){
	cin >> n >> m; 
	for (int i=0;i<m;i++){
		cin >> x >> y >> w;  
		adj[x].push_back({y,w});
		adj[y].push_back({x,w});
	}
}
void dijkstra(int s,int t){
	vector<long long> d(n+1,inf);
	vector<bool> visited(n+1,false);
	d[s]=0;
	pre[s]=s;
	priority_queue<pair<int,int> , vector<pair<int,int> > ,greater<pair<int,int> > > q;
	q.push({0,s});
	while (!q.empty()){
		pair<int, int > top= q.top();
        q.pop();
        int kc=top.first;
        int u=top.second;
        if (visited[u]) continue; 
        visited[u]=true;
        if (kc > d[u]) continue;
        for (int a=0;a < adj[u].size();a++){
        	int v = adj[u][a].first;
        	int w = adj[u][a].second;
        	if (d[v] > d[u] + w){
        		d[v] = d[u]+w;
        		q.push({d[v],v});
        		pre[v] = u;  
			}
		}
	}
	cout << d[t] << endl;
	vector<int> path;
    while (t != s){
		path.push_back(t);
		t=pre[t];
	}
	path.push_back(s);
	reverse(path.begin(),path.end());
	for (int i=0;i<path.size();i++){
	    cout << path[i]<< " ";
}
}
int main(){
	//setIO("DIJKSTRAHEAP");
	readin();
	dijkstra(1,n);
	return 0;
	//fi.close();
	//fo.close();
}





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
		freopen((name + ".out").c_str(), "w", stdout);
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
	setIO("QBMST");
	readin();
	//cout << n << m;
	prim_dt(1);
	return 0;	
}





















////////QHÐ

//Day con l?p l?i dài nh?t
#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inP").c_str(), "r", stdin); 
		//freopen((name + ".out").c_str(), "w", stdout);
	}
}
int n;
string s;
void readin(){
	cin >> n >> s;
}

void solve(){
	int dp[n+5][n+5];
	memset(dp,0,sizeof(dp));
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			if (s[i-1] == s[j-1] && i!=j) dp[i][j] = dp[i-1][j-1]+1;
			else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
		}
	}
	cout << dp[n][n];
}

int main(){
	//setIO("TEN FILE");
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
3
abc 
out:0
inp:
5
axxxy
out: 2*/





//Dãy con có t?ng b?ng S
#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inP").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

/*void readin(){
	cin >> n >> s;
	for (int i=1)
}*/

void solve(){
	int n,s,dp[1001],a;
	cin >> n >> s;
	dp[0]=1;
	for (int i=1;i<=n;i++){
		cin >> a;
		dp[a]=1;
		for (int j=s;j>=a;j--){
			if (dp[j-a]==1) dp[j]=1;
		}
	}
	if (dp[s]==1) cout <<"yes";
	else cout << "no";
}

int main(){
	//setIO("TEN FILE");
	//readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
inp:
5 6
1 2 4 3 5
out : yes*/




//dÃY CON LIÊN TI?P CÓ T?NG L?N NH?T
#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int a[1000],n,dp[10000],res,k;
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++){
		fi >> a[i];
	}
}
void solve(){
	int sum,best;
	for (int i=1;i<=n;i++){
		sum = max(a[i],sum+a[i]);
		best = max(sum,best);
	}
	cout << best;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
inp:
8
5 3 5 7 8 3 6 9
out:

*/



//Duong di nh? nh?t
#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int a[1000][1001],n,m,dp[1000][1001],res;
void readin(){
	fi >> n >>m;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			fi >> a[i][j];
			dp[i][j]=a[i][j];
		}
	}
}
void solve(){
    for (int i=1;i<=n;i++){
    	for (int j=1;j<=m;j++){
    		if (i==1&&j==1) dp[i][j]=dp[i][j];
    		else {
    			if (j==1) dp[i][j]=dp[i][j]+dp[i-1][j];
    			else {
    				if (i==1) dp[i][j]=dp[i][j]+dp[i][j-1];
    				else {
    					dp[i][j]= dp[i][j]+min(dp[i][j-1],min(dp[i-1][j],dp[i-1][j-1]));
    		           // res=max(res,dp[i][j]);
					}
				}
			}
			
		}
	}
	fo << dp[n][m];
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
inp:
3 3
1 2 3
4 8 2
1 5 3
out :
8
*/




// Dãy con tang dài nh?t
#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int a[1000],n,dp[10000],res,t[1001],jmax,g=0;
void readin(){
	cin >> n;
	for (int i=0;i<n;i++){
		cin >> a[i];
	}
}
void solve(){
	for (int i=0;i<n;i++){
		dp[i]=1;
		for (int j=0;j<i;j++){
			if (a[i]>a[j]) dp[i]=max(dp[i],dp[j]+1);
			/*if (res<dp[i]){
				res=dp[i];
			    jmax=j;
			}*/
			
		}
		//cout << dp[i]<< " ";
		//t[i]=jmax;
		res = max(res,dp[i]);
	}
	cout << res;
	
	/*
	cout << endl << res << " "<< jmax<< endl;
	for (int i=0;i<n;i++){
    	cout << a[i]<< " ";
	}
	cout << endl;
	for (int i=0;i<n;i++){
    	cout << dp[i]<< " ";
	}
	cout << endl;
    for (int i=0;i<n;i++){
    	cout << t[i]<< " ";
	}
	cout << endl;
	int max=0;
	for (int i=0;i<n;i++){
		if (dp[i]>dp[max])
		max=i;
	}
	while (true){
		int i=max;
		cout << a[i] << " ";
		max = t[i];
		if (t[max]==0){
			cout << a[max] << " ";
			break;
		}
	}*/
}
int main(){
	readin();
	solve();
	return 0;
	//fi.close();
	//fo.close();
}
/*
inp:
6
1 2 5 4 6 2
out:
4*/






///Dãy con có t?ng chia h?t cho K
#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,k,a[1001],t[1001];
void readin(){
	cin >> n >> k;
	for (int i=1;i<=n;i++) cin >> a[i];
	t[0]=0;
	for (int i=1;i<=n;i++) {
		t[i] = t[i-1]+a[i];
	}
}

void solve(){
	int max=0,d,c;
	for (int l=1;l<=n;l++){
		for (int r=l;r<=n;r++){
			if (((t[r]-t[l-1] )% k==0) && ((r-l)+1>max)){
				max= (r-l)+1; 
				d=l; 
				c=r;
			}
		}
	}
	cout << "day {";
	for (int i=d;i<=c;i++) cout << a[i] << " ";
	cout << "}="<<t[c]-t[d-1] << " mod k = "<<(t[c]-t[d-1])%k; 
}
int main(){
	readin();
	solve();
	//for (int i=1;i<=n;i++) cout << t[i] << " ";
	return 0;
	fi.close();
}
/*
int main(){
	int n,k,a,dp[1001][1001];
	cin >> n >> k;
	dp[0][0]=0;
	for (int i=1;i<k;i++) dp[0][i]=1005;
	for (int i=1;i<=n;i++){
		cin >> a;
		a%=k;
		for (int j=0;j<k;j++){
			dp[i][j] = max(dp[i-1][j],dp[i-1][(j+k-a)%k]+1);
		}
	}
	cout << dp[n][0];
}*/



/*
inp:
10 3
2 3 5 7 9 6 12 7 11 15
out:
9
*/





// hÌNH VUÔNG L?N NH?T
#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int a[1000][1001],n,m,dp[1000][1001],res;
void readin(){
	cin >> n >> m;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			cin >> a[i][j];
			dp[i][j]=a[i][j];
		}
	}
}
void solve(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			if (a[i][j]==0) continue;
			if (a[i][j]==a[i-1][j] && a[i][j]==a[i][j-1] && a[i][j]==a[i-1][j-1]){
				dp[i][j]=min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
			}
			res=max(res,dp[i][j]);
		}
	}
	cout << res<< endl;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){ 
		    cout << dp[i][j] << " ";
		}
		cout << endl;
	}
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
inp:
2
6 5
0 1 1 0 1
1 1 0 1 0
0 1 1 1 0
1 1 1 1 0
1 1 1 1 1
0 0 0 0 0
2 2 
0 0 
0 0
out :
3
0
*/




/// 3 x?u con chung dài nh?t
#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
string s1,s2,s3;
int dp[100][100][100],t,n,m,l;
void readin(){
	cin >> n >> m >> l >> s1 >> s2 >> s3;
	memset(dp,0,sizeof(dp));
}

void solve(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			for (int k=1;k<=l;k++){
				if (s1[i-1] == s2[j-1] && s2[j-1] ==  s3[k-1])
				    dp[i][j][k] = 1+ dp[i-1][j-1][k-1];
				else 
				    dp[i][j][k] = max(dp[i-1][j][k],max(dp[i][j-1][k],dp[i][j][k-1]));
		    }
		}
	}
	
	cout << dp[n][m][l] << endl;
}

int main(){
	/*fi >> t;
	while(t--){
		readin();
	    solve();
	}*/
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*inp:
5 8 13
geeks geeksfor geeksforgeeks
out:
5*/






//xAU CON CHUNG DÀI NH?T
#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
string s1,s2;
int dp[100][100],res,t;
void readin(){
	cin>> s1 >> s2;
	res=0;
}
void solve(){
	for (int i=1;i<=s1.size();i++){
		for (int j=1;j<=s2.size();j++){
			if (s1[i-1]==s2[j-1]) dp[i][j]=dp[i-1][j-1]+1;
			else {
				dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
			}
			res=max(dp[i][j],res);
			//fo << dp[i][j]<< " ";
		}
	    //cout << endl;	
	}
	cout << res<< endl;
	//cout << endl;
}
int main(){
	/*cin >> t;
	while (t--){
		readin();
		solve();
	}*/
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
2
AGGTAB
GXTXAYB
AA
BB
OUT:
4
0*/
-->
</html>
