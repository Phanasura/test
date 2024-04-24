#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt"); 
int n,m,s,t,y,x,w;
const int maxn = 100001;
vector <pair<int,int> > adj[maxn];
int pre[maxn];
void readin(){
	fi >> n >> m >> s >> t; // n:dinh m:canh s:vi tri xuat phat
	for (int i=0;i<m;i++){
		fi >> x >> y >> w;  // x,y: dinh   w:trong so
		adj[x].push_back({y,w});
		//adj[y].push_back({x,w});
	}
}
const int inf = 1e5;
void dijkstra(int s,int t){
	//Mang luu khoang cach duong di
	vector<long long> d(n+1,inf);
	vector<bool> visited(n+1,false);
	d[s]=0;
	pre[s]=s;
	priority_queue<pair<int,int> , vector<pair<int,int> > ,greater<pair<int,int> > > q;
	// {khoang cach, dinh}
	q.push({0,s});
	while (!q.empty()){
		//chon ra dinh co khang cach tu s nho nhat
		pair<int, int > top= q.top();
        q.pop();
        int kc=top.first;
        int u=top.second;
        if (visited[u]) continue; //dinh nay duoc xet roi
        visited[u]=true;
        //if (kc > d[u]) continue;
        //Relaxation: Cap nhat khoang cach tu s cho toi moi dinh ke voi u
        for (int a=0;a < adj[u].size();a++){
        	int v = adj[u][a].first;
        	int w = adj[u][a].second;
        	if (d[v] > d[u] + w){
        		d[v] = d[u]+w;
        		q.push({d[v],v});
        		pre[v] = u;  // truoc v la u
			}
		}
	}
	fo << d[t] << endl;
	vector<int> path;
    while (t != s){
		path.push_back(t);
		t=pre[t];
	}
	path.push_back(s);
	reverse(path.begin(),path.end());
	for (int i=0;i<path.size();i++){
	    fo << path[i]<< " ";
}
}
int main(){
	readin();
	dijkstra(s,t);
	return 0;
	fi.close();
	fo.close();
}
/*
inp:

out:

*/
