#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
//ofstream fo("kq.txt"); 
const int inf = 1e3;
int n,k,c[1001][1001],u,v,d[1001],pre[1001],tong,dmin;
bool visited[1001];
void readin(){
	fi >> n >> k; // n:dinh m:canh s:vi tri xuat phat

	while (!fi.eof()){
		fi >> u >> v >> c[u][v];  // x,y: dinh   w:trong so
		c[v][u]=c[u][v];
	}
	
	d[k]=0;
}

void dijkstra(){
	//Mang luu khoang cach duong d
	for (int i=1;i<=n;i++){
		u=0; dmin=inf;
		for (int j=1;j<=n;j++)
		    if (dmin>d[j] && !visited[j]){ 
		        u=j;
		        dmin = d[j];
			}
		if (u==0) break;
		visited[u]=true;
		for (int v=1;v<=n;v++){
			if (c[u][v]>0 && !visited[v]){
				if (d[v]>(d[u]+c[u][v])){
					d[v]=d[u]+c[u][v];
					pre[v]=u;
				}
			}
		}
	}
	tong =0;
	for (int i=1;i<=n;i++){
		tong = tong+c[i][pre[i]];
	}
	cout << tong<< endl;

	
}
int main(){
	memset(c,0,sizeof(c));
	memset(d,inf,sizeof(d));
	memset(visited,false,sizeof(visited));
	memset(pre,0,sizeof(pre));
	readin();
	dijkstra();
	return 0;
	fi.close();
	//fo.close();
}
/*
inp:

out:

*/
