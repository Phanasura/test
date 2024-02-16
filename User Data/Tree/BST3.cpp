#include <bits/stdc++.h>
#define file "test3"
#define ll long long
#define ld long double
#define ull unsigned long long
#define pii pair<ll, ll>
#define fi first
#define se second
#define maxn 100005
using namespace std;
const ll inf = 1e18;
struct Node
{
    int data;
    Node *left;
    Node *right;
};
typedef struct Node *Tree;
void Btree_init(Tree *root)
{
    (*root) = NULL;
}
void insert_node(Tree &T, int x)
{
    if (T == NULL)
    {
        Node *p = new Node;
        p->data = x;
        p->left = NULL;
        p->right = NULL;
        T = p;
    }
    else
    {
        if (x < T->data)
            insert_node(T->left, x);
        else
            insert_node(T->right, x);
    }
}
ll minValueRight(Tree T)
{
    Tree tmp = T;
    while (tmp != NULL && tmp->left != NULL)
    {
        tmp = tmp->left;
    }
    return tmp->data;
}

void delete_node(Tree &T, int x)
{
    if (T != NULL)
    {
        if (x < T->data)
        {
            delete_node(T->left, x);
        }
        else if (x > T->data)
        {
            delete_node(T->right, x);
        }
        else
        {
            // Node *p = T;
            if (T->right == NULL)
            {
                // cout << T->left->data << endl;
                T = T->left;
            }
            else if (T->left == NULL)
            {
                T = T->right;
            }
            else
            {
                ll tmp = minValueRight(T->right);
                T->data = tmp;
                delete_node(T->right, tmp);
            }
            // delete p;
        }
    }
}
void NLR(Tree T)
{
    if (T != NULL)
    {
        cout << T->data << " ";
        NLR(T->left);
        NLR(T->right);
    }
}
ll n;
ll a[maxn];
Tree T;

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen(file ".inp", "r", stdin);
//    freopen(file ".out", "w", stdout);
//#endif
//    ios_base::sync_with_stdio(0);
//    cin.tie(NULL);
//    cout.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        char test;
        cin >> test;
        if (test == '+')
        {
            ll x;
            cin >> x;
            insert_node(T, x);
        }
        else if (test == '-')
        {
            ll x;
            cin >> x;
            delete_node(T, x);
        }
    }
    // cout << T->left->data << endl;
    // T->left = T->left->left;
    NLR(T);
}

