#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
string s;
string s1;
int a[1001],p=0,k=0,t=1,d=0;
vector <string> v[1001];
pair<int,int> pa[1001];
bool check=true;
void readin(){
	//fi.ignore();
	fi >> s;
//	memset(s1,' ',sizeof(s1));
}
void xuat(int a,int b){
	s1=s.substr(a,b);
    v[t].push_back(s1);
    t+=1;
}
void solve(){
///	int p=0,k=0,d=0;
	int n = s.size();
	for (int i=0;i<n;i++){
		if (s[i] == '('){
			p+=1;
			a[p]=i;
		}
		else if (s[i] == ')'){
			if (p==0)  check =false;
			else {
				d+=1;
				k=i;
				s1="";
				///cout << a[p]<< " "<< k << endl;
				//cout << k << endl;
				//xuat(a[p],k);
				pa[d].first = a[p];
				pa[d].second =k;
				p-=1;
			}
		}
	}
	if (p>0) check =false;
	if (check) {
		cout << d<< endl;
		for (int i=1;i<=d;i++){
			for (int j=pa[i].first;j<=pa[i].second;j++){
				cout << s[j];
			}
			cout << endl;
		}
	}
	else cout << -1;
}
int main(){
	readin();
	solve();
	fi.close();
}
