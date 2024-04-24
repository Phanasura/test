#include <bits/stdc++.h>
using namespace std;
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inp").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

int n, k;
int a[100000];  
void readin(){
	cin >> n >> k;
	for (int i = 0;i<n;i++) {
        cin >> a[i];
    }
}

void solve(){
	int sum = 0,len = 0,kq = -1;
    for (int i = 0;i<n;i++) {
        sum = 0;
        len = 0;
        for (int j = i;j<n;j++) {
            sum += a[j];
            len++;
            double av =(double)sum/len;
            if (av >= k) {
                kq = max(kq,len);
            }
        }
    }
    if (kq == -1) {
        cout << "-1" << endl;
    } else {
        cout << kq << endl;
    }
}

int main() {
    setIO("Seq");
	readin();
	solve();
    return 0;
}

