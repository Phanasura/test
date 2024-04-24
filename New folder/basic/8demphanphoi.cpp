#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
int n,a[1001],spt,num[1001],sl[1001];
void readin(){
	fi >> n;
	for (int i=1;i<=n;i++){
		fi >> a[i];
	}
	sort(a+1,a+n+1);
}
void demphanphoi(){
	int i=1;
	spt=0;
	do {
		int key=a[i];
		i++;
		int dem=1;
		while (key==a[i] && i<=n){
			i++;
			dem++;
		}
		spt++;
		num[spt]=key;
		sl[spt]=dem;
	}while (i<=n);
}
void solve(){
	demphanphoi();
	for (int i=1;i<=spt;i++) cout <<"so "<<num[i]<<" co "<<sl[i] <<" phan tu"<< endl;
	cout << "cac phan tu xuat hien 1 lan la:";
	for (int i=1;i<=spt;i++)
	{
		if (sl[i]==1) cout << num[i]<< " ";
	}
	cout << endl << "so phan tu xuat hien nhieu lan la:";
	for (int i=1;i<=spt;i++)
	{
		if (sl[i]>1) cout << num[i]<< " ";
	}
}
int main(){
	readin();
	solve();
	return 0;
	fi.close();
}
