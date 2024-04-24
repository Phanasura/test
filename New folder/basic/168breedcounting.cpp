#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
int n,q,a[1001],l,r;
struct breed{
	int one,two,three;
};
void readin(){
	fi >> n >> q;
	for (int i=1;i<=n;i++) fi >> a[i];
}
breed pre[1001];
void solve(){
	if (l == 1) cout << pre[r].one << " " << pre[r].two << " " << pre[r].three;
	else cout << pre[r].one - pre[l-1].one << " " << pre[r].two - pre[l-1].two << " " << pre[r].three - pre[l-1].three;
}

int main(){
	readin();
	pre[0].one = pre[0].two = pre[0].three = 0;
	for (int i=1;i<=n;i++){
		if (a[i] == 1){
			pre[i].one = pre[i-1].one + 1;
			pre[i].two = pre[i-1].two;
			pre[i].three = pre[i-1].three;
		}
		else if (a[i] == 2){
			pre[i].two = pre[i-1].two + 1;
			pre[i].one = pre[i-1].one;
			pre[i].three = pre[i-1].three;
		}
		else if (a[i] == 3){
			pre[i].three = pre[i-1].three + 1;
			pre[i].one = pre[i-1].one;
			pre[i].two = pre[i-1].two;
		}
	}
	/*for (int i=1;i<=n;i++){
		cout << pre[i].one << " " << pre[i].two << " " << pre[i].three;
		cout << endl;
	}
	cout << endl;*/
	while (q--){
		fi >> l >> r;
		solve();
		cout << endl;
    }
	fi.close();
	fo.close();
	return 0;
}
/*
inp:
6 3
2
1
1
3
2
1
1 6
3 3
2 4
out:
3 2 1
1 0 0
2 0 1
*/
/*
code mau: 
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    // preprocess the counts of cows of each breed
    vector<int> holsteins(n+1), guernseys(n+1), jerseys(n+1);
    for (int i = 1; i <= n; i++) {
        int breed;
        cin >> breed;
        holsteins[i] = holsteins[i-1] + (breed == 1);
        guernseys[i] = guernseys[i-1] + (breed == 2);
        jerseys[i] = jerseys[i-1] + (breed == 3);
    }

    // answer the queries
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        int h = holsteins[b] - holsteins[a-1];
        int g = guernseys[b] - guernseys[a-1];
        int j = jerseys[b] - jerseys[a-1];
        cout << h << " " << g << " " << j << endl;
    }

    return 0;
}
*/
