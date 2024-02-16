#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
vector<int> v[1001];
vector<int> to;
int n,m,x,y;
bool visited[1001];
void readin(){
    fi >> n >> m;
    for (int i=1;i<=m;i++){
        fi >> x >> y;
        v[x].push_back(y);
    }
    memset(visited,false,sizeof(visited));
}
void dfs(int i){
    visited[i]=true;
    for (int j=0;j<v[i].size();j++){
        if (!visited[v[i][j]])
            dfs(v[i][j]);
    }
    to.push_back(i);
}
void solve(){
   for (int i=1;i<=n;i++){
        if (!visited[i]){
             dfs(i);
        }
   }
    reverse(to.begin(),to.end());
    for (int i=0;i<to.size();i++){
        cout << to[i]<< " ";
    }
}
int main(){
    readin();
    solve();
    return 0;
    fi.close();
}
