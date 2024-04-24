#include <bits/stdc++.h>
using namespace std;
ifstream fi("test.txt");
ofstream fo("");

int merge(int a[],int l, int m,int r){
	int n1 = m-l+1;
	int n2 = r-m;
	int L[n1],R[n2];
	
	for (int i=0;i<n1;i++){
		L[i] = a[l+i];
	}
	for (int i=0;i<n2;i++){
		R[i] = a[m+1+i];
	}
	int i=0,j=0,k=l;
	int res=0;
	
	while (i<n1 && j<n2){
		if (L[i] <= R[j]) a[k++] = L[i++];
		else {
			a[k] = R[j];
			j++; k++;
			res+=n1-i;
		}
	}
	while (i<n1) a[k++] = L[i++];
	while (j<n2) a[k++] = R[j++];
	
	return res;
}

int mersort(int a[],int l , int r){
	int res = 0;
	if (l < r){
		int m=(l+r)/2;
		res += mersort(a,l,m);
		res += mersort(a,m+1,r);
		res += merge(a,l,m,r);
	}
	return res;
}
int main(){
	int t;
	fi >> t;
	while (t--){
		int n;
		fi >> n ;
		int a[n];
		for (int i=0;i<n;i++){
			fi >> a[i];
		}
		cout << mersort(a,0,n-1) << endl;
	}
	return 0;
	fi.close();
	fo.close();
}
/*
inp:
2
5
2 4 1 3 5
5
5 4 3 2 1
out :
3
10
*/
