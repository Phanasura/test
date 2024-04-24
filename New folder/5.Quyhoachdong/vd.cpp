#include <iostream>
using namespace std;
int a[100][100],n,m;
int main(){
    cin >> n >> m;
    n = min(n,m);
	m = max(n,m); 
    for (int i=1;i<=m;i++){
      	a[1][i] = i;
      	a[i][1] = a[1][i];
      	//cout << a[1][i] << " " << a[i][1]; 
	}
    for (int i=2;i<=n;i++){
        for (int j=i+1;j<=m;j++){
            if (i==j-1) a[i][j-1]=1;
            a[i][j]=a[i][j-i]+1;
            a[j][i]= a[i][j]; 
            }
    }
    cout << a[n][m];
    for (int i=1;i<=m;i++){
        for (int j=1;j<=m;j++){
            cout << a[i][j] << " "; 
        }
        cout << endl; 
    }
    return 0;
 }
