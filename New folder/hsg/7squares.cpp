#include<bits/stdc++.h>
using namespace std; 
int main()
{
 
 int n,k,d,h;	
 cin >> n; 
 k=3;d=1;
 
 for(int i=1; i<=n; i++)
  { 
   d=d+k; 
   k=k+2; 
  }
 h=d % 2013;
 cout << h ; 
}





