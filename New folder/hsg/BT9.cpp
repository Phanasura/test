#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
ifstream fi("BT9.inp");
ofstream fo("BT9.out");
int main() {
    string s; 
	fi >> s;

    sort(s.begin(), s.end());
    string res;
    int count = 0;
    do {
        count++;
        res += s;
        res += '\n';
    } while(next_permutation(s.begin(), s.end()));

    fo << count << '\n';
    fo << res;
    return 0;
    fi.close();
    fo.close();
}
