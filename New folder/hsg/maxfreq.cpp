#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("kq.txt");
int spt,key,n,a[1000],num[1000],sl[1000],dem;
void readin(){
    fi >> n;
    for (int i = 1;i<=n;i++){
        fi >> a[i];
    }
}
void dpp(){
	sort(a+1,a+n+1);
	spt=0;
	int i=1;
	do{
	   key=a[i];
	   dem=1;
	   i++;
	   while ((a[i]==key) and (i<=n)){
	   	dem++;
	   	i++;
	   }
	   spt++;
	   num[spt]=key;
	   sl[spt]=dem;
	}while (i<=n);
}
void solve(){
    dpp();
    for (int i=1;i<=spt;i++){
		fo << num[i]<<" ";
	}
	fo<<endl;
	
	for (int i=1;i<=spt;i++){
		fo << sl[i]<< " ";
	}
	/*int max1=INT_MIN;
	int max2=INT_MIN;
	for (int i=1;i<=spt;i++){
		if (max1<sl[i]) {
			max1=sl[i];
			max2=i;
		}
	}
	fo << num[max2]<<" "<< max1;
	fo<<endl;
	
	/*for (int i=1;i<=spt;i++){
		fo << sl[i]<< " ";
	}*/
}
int main(){
    readin();
    solve();
    return 0;
    fi.close();
    fo.close();
}
/*cach 2:
#include<bits/stdc++.h>
using namespace std;
long long n, a[10000001], l[1000001], lmax;
int main() {
	freopen("maxfreq.inp","r",stdin);
	freopen("maxfreq.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	for(int i=1;i<=n;i++) {
		if(a[i-1]==a[i]) l[i]=l[i-1]+1;
		else l[i]=1;
	}
	for(int i=1;i<=n;i++) lmax=max(lmax,l[i]);
	cout<<lmax<<endl;
	for(int i=1;i<=n;i++) {
		if(l[i]==lmax) cout<<a[i]<<endl;
	}
}
*/


