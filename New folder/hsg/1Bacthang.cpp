#include <bits/stdc++.h>
using namespace std;
long long n ;
string sum(string s, string x)
{
    string c="";
    while (s.size() < x.size()) s="0"+s;
    while (x.size() < s.size()) x="0"+x;
    int nho=0, t=0;
    for (int i=s.size()-1;i>=0;i--)
    {
        t= (s[i] - 48 ) + (x[i] -48) +nho;
        if (t>9)
        {
            nho=1;
            t=t-10;
        }
        else nho=0;
        char d= t+'0';
        c=d+c;
    }
    if (nho==1) c="1"+c;
    return c;
}
int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    freopen("Bacthang.inp","r",stdin); freopen("Bacthang.out","w",stdout);
    cin >> n;
string f[10001];
    f[1]="1";
    f[2]="2";
    for (int i=3;i<=n;i++) f[i]=sum(f[i-1],f[i-2]);
    cout << f[n];
return 0;
}
