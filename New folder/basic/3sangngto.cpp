#include <iostream>
#include <math.h>
using namespace std;
const int MAXSANG = 1000;
 
int snt[MAXSANG+1];
 
void sangnt()
{
    long i,j;
    for (i=1; i<=MAXSANG; i++)
        snt[i]=1;
    snt[1]=0;
    i=2;
    while (i<=sqrt(MAXSANG))
    {
        while (snt[i]==0)
            i++;
        for (j=2; j<=MAXSANG/i; j++)
            snt[i*j]=0;
        i++;
    }
}
 
int main()
{
    sangnt();
 for (int i=1; i<=1000; i++)
 if (snt[i]) cout<< i<<endl;
    return 0;
}
