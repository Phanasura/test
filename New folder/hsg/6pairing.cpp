#include<bits/stdc++.h>
using namespace std;
int main() {
    freopen("pairing.inp","r",stdin);	
	freopen("pairing.out","w",stdout);
	int a,b,c,d,t,t1;
	cin >> a >> b>> c >> d;
	t=a+b;
	t1=c+d;
	if (a %2 ==0) {t=t-a; }else t=t-a-1;
	if (c %2 ==0) {t1=t1-c;} else t1=t1-c-1;
	if (((b+d)%2)==0) {
		t=t-b;
		t1=t1-d;
	} else {t=t-b-1;t1=t1-d-1;}
	cout << abs(t+t1);
	return 0;
}
