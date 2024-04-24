#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define ll long long
#define fi first
#define se second
using namespace std;

const int N = 2e5 + 5;

int n, cnt[N], a[N], sq[N], pos[N];
vector<int> v[2];
ll ans;

int main() {
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        sq[i] = sqrt(a[i]);
        cnt[a[i]]++;
        pos[a[i]] = i;
    }
    for(int i = 1; i <= n; ++i) {
        if(cnt[a[i]] > 1) {
            if(sq[i] * sq[i] == a[i]) v[0].pb(a[i]);
            else v[1].pb(a[i]);
        }
        else {
            if(sq[i] * sq[i] == a[i]) v[0].pb(a[i]);
            else {
                if(sq[i] * sq[i] > a[i]) v[1].pb(a[i]);
                else v[0].pb(a[i]);
            }
        }
    }
    sort(v[0].begin(), v[0].end(), greater<int>());
    sort(v[1].begin(), v[1].end());
    int d1 = v[0].size(), d2 = v[1].size();
    for(int i = 1; i <= n / 2; ++i) {
        if(i > d1 && i > d2) break;
        if(i > d1) ans += v[1][i - 1];
        else if(i > d2) ans += v[0][i - 1];
        else ans += min(v[0][i - 1], v[1][i - 1]);
    }
    cout << ans << '\n';
    return 0;
}

