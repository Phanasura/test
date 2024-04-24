#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int d,m,y,s;
void readin(){
	fi >> d >> m >> y;
}

void solve(){
	s=d;
	for (int i=1;i<m;i++){
		if (i==1||i==3||i==5||i==7||i==8||i==10||i==12) s=s+31;
		if (i==4||i==6||i==9||i==11) s=s+30;
		if (i==2){
			if ((y%4==0)||(y%400==0&&y%100!=0)) s=s+29;
			else s=s+28;
		}
	}
	cout << s;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
