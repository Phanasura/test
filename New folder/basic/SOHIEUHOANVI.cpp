#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
//ofstream fo("SOHIEUHOANVI.OUT");
int n, a[15];

int fact(int n) {
    if (n == 0) return 1;
    return n * fact(n-1);
}

void readin(){
	n=0;
    while (!fi.eof()){
    	n++;
		fi >> a[n];
	}
	n--;
}

void solve(){
	int ans = 0;
    for (int i = 1; i <= n; i++) {
        int count = 0;
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i]) {
                count++;
            }
        }
        ans += count * fact(n-i);
    }
    cout << ans+1 << endl;
}

int main(){
	readin();
	solve();
	return 0;
	fi.close();
	//fo.close();
}

