#include <bits/stdc++.h>
using namespace std;

long long n,a[1000000],b[1000000],s[1000000],i,j,maxx,tam,chia,du;
bool kt[1000000],x;
void sangnt(long long n)
{
    long long i,j;
    for ( i=1;i<=n;i++) kt[i]=true;
    kt[1]=false;
    tam=sqrt(n);
    for ( i=2;i<=tam;i++)
    {
        for ( j=i*2;j<=n;j+=i) kt[j]=false;
    }
}

int main()
{
    ifstream fi ("ntvong.inp.txt");
    ofstream fo ("ntvong.out.txt");
	fi>>n;
    maxx=0;
    for (i=1;i<=n;i++)
    {
        fi>>a[i]>>b[i];
        if (b[i]>maxx ) maxx=b[i];
    }
    long long k;
    k=1;
    while (k<=maxx) k=k*10;
    maxx=k;
    sangnt(maxx);
    s[1]=0;
    for (i=2;i<10;i++)
        if(kt[i]==true) s[i]=s[i-1]+1;
        else s[i]=s[i-1];
    chia=1;
   for (i=10;i<=maxx;i++)
    {
        if (chia*10==i) chia=i;
        if (kt[i]==true)
        {
            tam=i;
            du=tam/chia;
            tam=((tam%chia)*10)+du;
            x=true;
            while (tam!=i & x==true)
            {
                if (kt[tam]==false) {x=false;break;}
                du=tam/chia;
                tam=((tam%chia)*10)+du;
            }
            if (x==true) s[i]=s[i-1]+1;
            else s[i]=s[i-1];
        }
        else s[i]=s[i-1];
    }
    for (i=1;i<=n;i++)
    {
        if ((s[b[i]]>s[b[i-1]] & s[a[i]]>s[a[i-1]]) || s[a[i]]>s[a[i-1]]) fo<<s[b[i]]-s[a[i]]+1<<endl;
        else fo<<s[b[i]]-s[a[i]]<<endl;
    }
    fi.close();
    fo.close();
    return 0;
}

