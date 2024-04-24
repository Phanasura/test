#include <bits/stdc++.h>
using namespace std;
int n,m,a[1001],pre[1001],cnt[1001],kq=0,value[1001];
const int inf = 100000;
bool visited[1001];
void readin(){
	cin >> n >> m;
	for (int i=1;i<=n;i++){
		cin >> a[i];
	}
	sort(a+1,a+n+1,greater<int>());
}

void solve(){
	cnt[0] = 0;
	for (int x=1;x<=m;x++){
		cnt[x] = inf;
		for (int i=1;i<=n;i++){
			if (x-a[i] >= 0 && cnt[x-a[i]]+1 < cnt[x]){
				cnt[x] = cnt[x-a[i]] + 1;
				pre[x] = a[i];
			}
		}
	}
	cout << cnt[m]<< endl;
	while (m>0){
		cout << pre[m] << " ";
		m-=pre[m];
	}
}
int main(){
	readin();
	solve();
	//for (int i=1;i<=n;i++) cout << a[i] << " ";
	return 0;
}
