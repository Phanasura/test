#include <bits/stdc++.h>
using namespace std;
ifstream fi("Thap.inp");
ofstream fo("Thap.out");
int n;
void readin(){
	fi >> n;
}

void solve(){
	stack<int> tower;
    for (int i = 0; i < n; i++) {
        int c;
        fi >> c;
        while (!tower.empty() && tower.top() <= c) {
            tower.pop();
        }
        tower.push(c);
    }
    fo << tower.size() << endl;
}

int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
