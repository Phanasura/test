#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");
string s;
void readin(){
	cin >> s;
}

void solve(){
	stack<long long> stk;
	int len = s.size();
	for (int i=0;i<len;i++){
		if (s[i] == '+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='%'||s[i]=='^'){
			long long a = stk.top(); stk.pop();
			long long b = stk.top(); stk.pop();
			long long tmp;
			if (s[i]=='+') tmp=b+a;
			else if (s[i]=='-') tmp=b-a;
			else if (s[i]=='*') tmp=b*a;
			else if (s[i]=='/') tmp=b/a;
			else if (s[i]=='%') tmp=b%a;
			else if (s[i]=='^'){
				tmp=b;
				for (int i=0;i<a-1;i++) tmp*=b;
			}
			stk.push(tmp);
		}
		else{
			stk.push((long long)(s[i]-'0'));
		}
	}
	cout << stk.top()<<endl;
}

int main(){
	readin();
	solve();
	return 0;
	fi.close();
	fo.close();
}
