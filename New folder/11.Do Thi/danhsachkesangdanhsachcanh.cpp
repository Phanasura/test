#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int n,x=0,a[100][100];
string s,num;
void init(){
	for (int i=1;i<=n;i++){
    	for (int j=1;j<=n;j++){
    		a[i][j]=0;
		}
	}
}
void readin(){
	fi >> n;
	fi.ignore();
	init();
	for (int i=1;i<=n;i++){
		getline(fi,s);
		stringstream ss(s);
		while (ss >> num){
			a[i][atoi(num.c_str())]=1;
		}
	}
}
void solve(){
    for (int i=1;i<=n;i++){
    	for (int j=1;j<=n;j++){
    		if (a[i][j]==1 && a[j][i]==1 ){
    			fo << i<< " "<<j;
    			a[j][i]=0;
    			fo << endl;
			}
		}
		
	
	}
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
inp:
5
2 3 4 
1 3 4 5 
1 2 4 5 
1 2 3 5 
2 3 4 
out:
0 1 1 1 0 
1 0 1 1 1 
1 1 0 1 1 
1 1 1 0 1 
0 1 1 1 0 
*/

