#include<bits/stdc++.h>
#define ll long long
#define MAX 100000
using namespace std;

struct node{
    ll data;
    node* left;
    node* right;
};

typedef node* Tree;
bool check[MAX+9];
ll n,a[MAX+9],cnt,dem,x,k;
Tree root;

void sieve()
{
    memset(check,true,sizeof(check));
    check[0]=false;
    check[1]=false;
    for (ll i=2;i<=MAX;i++)
    {
        if (check[i])
        for (ll j=i*i;j<=MAX;j+=i) check[j]=false;
    }
}

void insertnode(Tree &t, ll x)
{
    if (t==NULL)
    {
        node *p=new node;
        p->data=x;
        p->left=NULL;
        p->right=NULL;
        t=p;
    }
    else
    {
        if (x<t->data) insertnode(t->left,x);
        else insertnode(t->right,x);
    }
}

void NLR(Tree t)
{
    if (t!=NULL)
    {
        if (check[t->data]) cnt++;
        if (t->data==x) dem++;
        NLR(t->left);
        NLR(t->right);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //freopen("BST2.inp","r",stdin);
    //freopen("BST2.out","w",stdout);

    cin>>n;
    for (long i=1;i<=n;i++) cin>>a[i];
    cin>>k;
    if (k==2) cin>>x;

    for (long i=1;i<=n;i++) insertnode(root,a[i]);

    sieve();
    NLR(root);
    if (k==1) cout<<cnt;
    else
    {
        if (dem>0) cout<<"YES"; else cout<<"NO";
    }

    return 0;

}

