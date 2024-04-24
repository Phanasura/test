#include <bits/stdc++.h>
using namespace std;
//ifstream fi("test.txt");
ifstream fi("Inside.Inp");
ofstream fo("Inside.Out");
int n,a[1001][1001],d[1001];
void readin(){
    fi >> n;
    for (int i = 0; i < n-1; i++) {
        fi >> a[i][0] >> a[i][1];
    }
    fi >> a[n-1][0] >> a[n-1][1];
    fi >> d[0] >> d[1];
}

void solve(){
	int count = 0;
    int e[] = {10001, d[1]};
    for (int i = 0; i < n; i++) {
    int j = (i+1)%n;
    if ((a[i][1] > d[1]) != (a[j][1] > d[1])) {
        double check = (double)(a[j][0] - a[i][0]) * (double)(d[1] - a[i][1]) / (double)(a[j][1] - a[i][1]) + a[i][0];
        if (d[0] < check) {
            count++;
        }
    }  
    }
    if (count % 2 == 1) {
        fo << "1\n";
    } else {
    	fo << "0\n";
    }
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
