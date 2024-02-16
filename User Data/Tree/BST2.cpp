#include<bits/stdc++.h>
using namespace std;
const int MaxN = 1e6+5;
bool isPrime[MaxN+1];
bool isPrime1[MaxN+1];
int c,dem=0,x;
struct node{
	int data;
	node *left;
	node *right;
};

typedef node*Tree;
void insertnode(Tree &t, int x){
	if (t==NULL){
		node *p=new node;
		p->data=x;
		p->left=NULL;
		p->right=NULL;
		t=p;
	}
	else {
		if (x<t->data) insertnode(t->left,x);
		else insertnode(t->right,x);
	}
}

void sangnt() {
	for (int i = 2; i <= MaxN; i++){
		isPrime[i] = true;
		isPrime1[i] = false;
	}
	for (int i = 2; i <= MaxN; i++) {
    	if (isPrime[i] == true) {
    		for (int j = 2 * i; j <= MaxN; j += i) {
        		isPrime[j] = false;
      		}
    	}
  	}
}

void dNLR(Tree t){
	if (t!=NULL){
		if (isPrime[t->data]==true) dem++;
		isPrime1[t->data]=true;
		dNLR(t->left);
		dNLR(t->right);
	}
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen("BST2.INP","r",stdin);
//	freopen("BST2.OUT","w",stdout);
	int n;
	cin >> n;
	sangnt();
	Tree t; t=NULL;
	for (int i = 1; i <= n; i++){
		int x;
		cin >> x;
		insertnode(t, x);
	}
	cin >> c >> x;
	dNLR(t);
	if (c == 1) cout << dem;
	else if (isPrime1[x]==true) cout << "YES";
	else cout << "NO";
}

