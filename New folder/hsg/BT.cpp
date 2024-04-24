#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ifstream fi("BT.inp");
ofstream fo("BT.out");
char digit[20] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                  'A', 'B', 'C', 'D', 'E', 'F'};

char sosangchucai(int k)
{
    k += 48;
    return (char)k;
}

int toInt(char c)
{
    return int(c) - int('0');
}

string toString(ll n)
{
    string res = "";
    while (n != 0)
    {
        res = sosangchucai(n % 10) + res;
        n /= 10;
    }
    return res;
}

long long chuoisangso(string n)
{
    ll res = 0;
    for (int i = 0; i < n.length(); i++)
        res = res * 10 + toInt(n[i]);
    return res;
}

string ttps(string n, int b)
{
    string res = "";
    ll m = chuoisangso(n);
    while (m != 0)
    {
        res = digit[m % b] + res;
        m /= b;
    }
    return res;
}

string stp(string n, int b)
{
    ll base = 1, res = 0, num;
    for (int i = n.length() - 1; i >= 0; i--)
    {
        if ('A' <= n[i] && n[i] <= 'F')
        {
            num = int(n[i]) - 55;
        }
        else
            num = toInt(n[i]);
        res += num * base;
        base *= b;
    }
    return toString(res);
}

int main()
{
    string n;
    ll a, b;
    cin >> a >> b;
    cin >> n;
    if (a == b)
        cout << n;
    else if (a == 10)
        cout << ttps(n, b);
    else if (b == 10)
        cout << stp(n, a);
    else
        cout <<ttps(stp(n, a), b);
    fi.close();
    fo.close();
}
