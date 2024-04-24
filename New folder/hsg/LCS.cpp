#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int dp[MAXN][MAXN];
char s[MAXN], t[MAXN];

string ans;
 
//ifstream fi("test.txt");
ifstream fi("lcs.inp");
ofstream fo("LCS.out");

void readin(){	
    fi >> s >> t;
}

void solve(){
	int n = strlen(s), m = strlen(t);
	for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (s[i-1] == t[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s[i-1] == t[j-1]) {
            ans += s[i-1];
            i--;
            j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(ans.begin(), ans.end());
    fo << ans;
}

int main() {
    readin();
    solve();
    fi.close();
    fo.close();
    return 0;
}
