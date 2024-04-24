#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
string s;
void readin(){
	fi >> s;
}
void solve(){
	int a=0;
	for (int i=0;i<s.size()-1;i++){
		int x=0; int z=0;
		if (s[i]=='M') x=1000;
		else if (s[i]=='D') x=500;
		    else if (s[i]=='C') x=100;
		        else if (s[i]=='L') x=50;
		            else if (s[i]=='X') x=10;
		             else if (s[i]=='V') x=5;
		                  else if (s[i]=='I') x=1;
	    if (s[i+1]=='M') z=1000;
		else if (s[i+1]=='D') z=500;
		    else if (s[i+1]=='C') z=100;
		        else if (s[i+1]=='L') z=50;
		            else if (s[i+1]=='X') z=10;
		             else if (s[i+1]=='V') z=5;
		                  else if (s[i+1]=='I') z=1;
		if (x>=z){
		    a=a+x;
	    }
    	else {
    		a=a+(z-x);
    		i++;
		}
		if (i==s.size()-1 && x>=z){
			if (s[i]=='M') z=1000;
		    else if (s[i]=='D') z=500;
		    else if (s[i]=='C') z=100;
		        else if (s[i]=='L') z=50;
		            else if (s[i]=='X') z=10;
		             else if (s[i]=='V') z=5;
		                  else if (s[i]=='I') z=1;
		    a=a+z;
		    break;
		}

	
	}
	
	cout << a;
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
