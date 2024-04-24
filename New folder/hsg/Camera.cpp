#include <bits/stdc++.h>
using namespace std;

int n,k,r,t;
bool a[1005];

void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

void readin(){
	cin >> n >> k >> r >> t;
	for (int i=1;i<=k;i++){
		int x;
		cin>>x;
		a[x]=true;
	}
}

void solve(){
	//sort(a+1,a+n+1);
	int dem=0;
	int res=0;
	vector<int> kq;
    for (int i=1;i<=r;i++) if (a[i]) dem++;
    int left=1, right=r;
    while (left<=n-r+1){
	    int rtmp=right;	
	    while (dem<t && rtmp>=left ){
		    if (a[rtmp] == false) {
				a[rtmp]=true;
			    dem++;
			    res++;
			    kq.push_back(rtmp);
			    rtmp--;
		    }else rtmp--; 
	    } 
	    if (a[left]==true) dem--;
	    left++;
	    right++;
	    if (a[right] == true) dem++;
    }
    cout << res << endl;
    for (auto x : kq) cout<<x<<" ";
}
int main(){
	//setIO("Camera");
	readin();
	solve();
	return 0;
}
