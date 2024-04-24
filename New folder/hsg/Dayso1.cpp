#include <bits/stdc++.h>
using namespace std;
ifstream fi("Dayso1.inp");
ofstream fo("Dayso1.out");
int m, n;
int main(){
	cin >> m >> n;
	vector<int> a(m), b(n);
	for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int i = 0, j = 0, count = 0;
    while (i < m && j < n) {
        if (a[i] < b[j]) {
            count += n - j;
            i++;
        } else {
            j++;
        }
    }
    cout << count << endl;
	fi.close();
	fo.close();
	return 0;
}
