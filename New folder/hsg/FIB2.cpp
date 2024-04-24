#include <bits/stdc++.h>
using namespace std;
int t;
void setIO(string name = "") { 
	ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".in").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

void readin(){
    cin >> t;
}

void solve(){
	while (t--)
    {
        int n, k;
        cin >> n >> k;
        string f0 = "a", f1 = "b", fn;
        if (n == 0)
            fn = f0;
        else if (n == 1)
            fn = f1;
        else
        {
            for (int i = 2; i <= n; i++)
            {
                fn = f0 + f1;
                f0 = f1;
                f1 = fn;
            }
        }
        int cnt = 0;
        for (int i = 0; i < k; i++)
        {
            if (fn[i] == 'a')
                cnt++;
        }
        cout << cnt << endl;
    }
}

int main(){
	setIO("fib2");
	readin();
	solve();
	return 0;
}

