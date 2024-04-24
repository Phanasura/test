#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
string s;
int res;
void readin(){
	fi >> s;
}

void solve(){
    for (int i=0;i<s.size();i++){
		//le
		int u=i,v=i;
    	while (u>=0 && v<s.size()){
    		if (s[u]==s[v]){
    			res=max(res,v-u+1);
    			u--; v++;
			}
			else break;
		}
		//chan
		u=i,v=i+1;
		while (u>=0 && v<s.size()){
			if (s[u]==s[v]){
				res=max(res,v-u+1);
    			u--; v++;
			}
			else break;
		}
	}	
	cout << res<< endl;
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
2
ababadd
abscbads
out:
5
5
*/
