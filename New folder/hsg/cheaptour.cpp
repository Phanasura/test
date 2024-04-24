#include <bits/stdc++.h>
#define oo 1000000000;
using namespace std;
typedef pair<int,int> II;
    int n,u,v,k,c[17][17],cl[1000000][17],kc[1000000][17];
    II q[1000000];
void loang()
{
    for(int i=1; i<(1<<n); i++)
        for(int j=0; j<=n; j++)
    {
        kc[i][j]=oo;
        cl[i][j]=0;
    }
    int l=1, r=0;
    q[++r]=II(0,0); cl[0][0]=1; kc[0][0]=0;
    while(l<=r)
    {
        II t=q[l++];
        u=t.first, k=t.second;
        for(int i=1; i<=n; i++)
        {
            if((u&(1<<(i-1)))==0)
            {
                v=u|(1<<(i-1));
                kc[v][i]=min(kc[v][i],kc[u][k]+c[k][i]);
                if(cl[v][i]==0)
                {
                    cl[v][i]=1;
                    q[++r]=II(v,i);
                }
            }
        }
    }
    int ds=oo;
    for(int i=1; i<=n; i++)
        ds=min(ds,kc[(1<<n)-1][i]);
    cout<<ds;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        cin>>c[i][j];
    loang();
}
