#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int arr[1001],n;
void readin(){
	fi >> n;
	for (int i=0;i<n;i++) fi >> arr[i];
}
void solve(){
	int best = INT_MIN,sum;
    for (int i = 0; i < n; i ++) {
        sum = 0;
        for (int j = i; j < n; j ++) {
            sum += arr[i];
            best = max(best, sum);
        }
    }
    cout << sum;
}
int main(){
    readin();
    solve();
    return 0;
    fi.close();
}
