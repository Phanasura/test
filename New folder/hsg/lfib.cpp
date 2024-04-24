#include <bits/stdc++.h>
using namespace std;
string f[405];
string sum(string s, string x)
{
    while (s.size() < x.size()) s="0"+s;
    while (x.size() < s.size()) x="0"+x;
    int nho=0,base='0';
    string res;
    for (int i=s.size()-1;i>=0;i--)
    {
        int t = (s[i] - base) + (x[i] - base) + nho;
        if (t>9)
        {
            t= t-10;
            nho=1;
        }
        else nho=0;
        char d=t+base;
        res= d+res;
    }
    if (nho == 1 ) res="1" + res;
    return res;
}
bool cmp(string s, string x)
{
    if (s.size() != x.size()) return false;
    for (int i=0;i<s.size();i++) if (s[i] !=x[i]) return false;
    return true;
}
int main()
{
    long long T;
    cin >> T;
    f[1]="1";
    f[2]="1";
    for (int i=3;i<=400;i++)
    {
        f[i] = sum(f[i-1] , f[i-2]);
    }

    while (T--)
    {
        string s;
        long long i, j;
        cin >> i >> j >> s;
        string cnt = sum(f[i] , f[j]);
        if (!cmp(s,cnt)) cout << "NO"; else cout << "YES";
        cout << endl;
    }
return 0;
}