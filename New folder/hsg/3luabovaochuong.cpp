#include <bits/stdc++.h>
typedef unsigned long long ll;
using namespace std;
int tims(char *s){
	int n,dem[256],ma;
	for (int i=0;i<256;i++) dem[i]=0;
	
	for (int i=0;i<strlen(s);i++){
    	
    	if (isdigit(s[i]))     //("0" <s[i] || s[i]  > "9") {
    		ma=atoi(s[i]);
		else{
			ma= (int) s[i];
			if (ma>90) ma-=32;
	    }  
    	
		dem[ma]++;
    	
	}
	int max = dem[2];
	
	for (char j=65;j<91;j++){
		
		if (dem[j]>max) max = dem[j];
		
	}
	return max;
}
int timso(){
	
	for (int i=0;i<n;i++) c[i]=0;
	maxa = a[0]
	for (int i=0;i<n;i++) if (a[i]>maxa) maxa=a[i];
	for (int i=0;i<maxa;i++) {
		c[a[i]] = c[a[i]] +1;
	}
	
}
int main(){
	char *s;
	cout <<"\nnhap van ban:"; cin >> s;
    cout << tims(s);
    
    
	return 0;
}
