#include <bits/stdc++.h>
using namespace std;

ifstream fi("VLN.INP");
ofstream fo("VLN.OUT");

int n, h;
void readin(){
    fi >> n >> h;
}

void solve(){
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
        fi >> a[i];
    }
	int ans = 0;
    for (int i = 0; i < n; i++) {
        int curr = 0;
        for (int j = 0; j < n; j++) {
            if (abs(j-i)*3 <= h) {
                curr += a[j];
            }
        }
        ans = max(ans, curr);
    }
    fo << ans << endl; 
}
int main() {
    readin();
	solve();
    fi.close();
	fo.close();
	return 0;
}

