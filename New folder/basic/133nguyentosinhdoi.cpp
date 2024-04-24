#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,k,a[1001],snt[1001];
void readin(){
	fi >> n >> k;
}
void sangnt()
{
    long i,j,dem=0;
    for (i=1; i<=n; i++)
        snt[i]=1;
    snt[1]=0;
    i=2;
    while (i<=sqrt(n))
    {
        while (snt[i]==0)
            i++;
        for (j=2; j<=n/i; j++)
            snt[i*j]=0;
        i++;
    }
    for (int i=2;i<=n;i++) if (snt[i]) {
    	dem+=1;
		a[dem]=i;
	}
}
void solve(){
	sangnt();
	int d=0;
	for (int i=2;i<=n-k;i++){
		if (snt[i] && snt[i+k])
		 d++;
	}
	cout << d;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
