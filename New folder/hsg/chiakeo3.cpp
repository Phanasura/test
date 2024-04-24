#include <bits/stdc++.h>
using namespace std;

ifstream fi("test.txt");
ofstream fo("kq.txt");

int kid,candy,equaldiv,moddiv,way;

void enter(){
	fi >> kid >> candy;
}

void bt(int each,int candy,int remaincandy){
	if (each > kid){
		if (remaincandy == 0) way++;
		return;
	}
	for (int i=candy;i>=1;i--){
		if ((each<=kid)&&(remaincandy>=0)) bt(each+1,i,remaincandy-i);
	}
}

void solve(){
	bt(1,candy,candy);
	fo << way<<endl;
	equaldiv=candy/kid;
	moddiv=candy%kid;
	for (int i=1;i<=moddiv;i++){
		fo << equaldiv+1<<" ";
	}
	for (int i=moddiv+1;i<=kid;i++){
		fo << equaldiv<<" ";
	}
}

int main(){
	enter();
	solve();
	return 0;
	fi.close();
	fo.close();
}
/*
inp:
3 5
out:
2
2 2 1
*/
