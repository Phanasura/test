#include <bits/stdc++.h>
using namespace std;

int main() {
    //ifstream in("BRACKET.INP");
    //ofstream out("BRACKET.OUT");
    //ifstream in("test.txt");
    string s;
    cin >> s;
    long long n = s.size(), ans = 0;
    stack<long> st;
    for (long long i = 0; i < n; i++) {
        if (s[i] == '(') st.push(i);
        else {
            if (st.empty()) ans++;
            else st.pop();
        }
    }
    ans += st.size();
    cout << ans;
    return 0;
}
