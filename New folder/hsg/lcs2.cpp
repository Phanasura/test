#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;

string a,b;
int M, N, A[MAXN], B[MAXN], dp[MAXN][MAXN], trace[MAXN][MAXN];
void setIO(string name = "") { 
    ios_base::sync_with_stdio();
	cin.tie(0);  cout.tie(0);
	if (!name.empty()) {
		freopen((name + ".inP").c_str(), "r", stdin); 
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

void readin(){
	getline(cin, a);
	getline(cin, b);
	int cnt = 0;
	for (int i=0 ; i<a.size() ; i++){
		if (a[i] <= '9' && a[i] >= '0'){
			cnt += 1;
		    A[cnt] = a[i];
		    M = cnt;
		}
	}
	cnt = 0;
	for (int i=0 ; i<b.size() ; i++){
		if (b[i] <= '9' && b[i] >= '0'){
			cnt +=1 ;
		    B[cnt] = b[i];
		    N = cnt;
		}
	} 
	for (int i=1 ;i<=M;i++) cout << A[i] << " ";
	cout << endl;
	for (int i=1 ;i<=N;i++) cout << B[i] << " ";
	
}

void findLCS(int i, int j) {
    if (i == 0 || j == 0) return;
    if (trace[i][j] == 1) {
        findLCS(i-1, j-1);
        cout << A[i] << " ";
    } else if (trace[i][j] == 2) {
        findLCS(i-1, j);
    } else {
        findLCS(i, j-1);
    }
}

void solve(){
    memset(dp, 0, sizeof(dp));
    memset(trace, 0, sizeof(trace));

    
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (A[i] == B[j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                trace[i][j] = 1; 
            } else {
                if (dp[i-1][j] >= dp[i][j-1]) {
                    dp[i][j] = dp[i-1][j];
                    trace[i][j] = 2; 
                } else {
                    dp[i][j] = dp[i][j-1];
                    trace[i][j] = 3;
                }
            }
        }
    }

    cout << dp[M][N] << "\n";
    findLCS(M, N);

}

int main(){
	//setIO("LCS");
	readin();
	//solve();
	
	return 0;
}
