#include <bits/stdc++.h>
#define INF int64_t(1e9)
#define pii pair <int, int>
#define pll pair <long long, long long>
#define file "test"
using namespace std;
const int nmax=1e6;
const int MOD = 1e9 + 7;

struct Node
{
    int data;
    Node *left;
    Node *right;
};
typedef struct Node *Tree;
void insertNode(Tree &T, int x)
{
    if (T == NULL)
    {
        Node *p = new Node;
        p -> data = x;
        p -> left = p -> right = NULL;
        T = p;
    }
    else if (x < T->data) insertNode(T->left, x);
    else insertNode(T->right, x);
}

Tree deleteNode(Tree T, int x)
{
    if (T==NULL) return T;
    if (x < T->data)
    {
        T -> left = deleteNode(T -> left, x);
        return T;
    }
    else if (x>T->data)
    {
        T -> right = deleteNode(T -> right, x);
        return T;
    }

    if (T->left == NULL)
    {
        Tree tmp = T->right;
        delete T;
        return tmp;
    }
    if (T->right == NULL)
    {
        Tree tmp = T->left;
        delete T;
        return tmp;
    }
    else
    {
        Tree par = T;
        Tree cur = T->right;
        while (cur -> left != NULL)
        {
            par = cur;
            cur = cur -> left;
        }
        if (par != T)
            par -> left = cur -> right;
        else
            par -> right = cur -> right;
        T -> data = cur -> data;
        delete cur;
        return T;
    }

}
void travel(Tree T)
{
    if (T != NULL)
    {
        cout << T->data << " ";
        travel(T->left);
        travel(T->right);
    }
}
int n;
Tree T;
int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    //freopen(file".inp","r",stdin);
    //freopen(file".out","w",stdout);
    cin >> n;
    for (int i=1,x;i<=n;i++)
    {
        char type;
        cin >> type >> x;
        if (type == '+') insertNode(T, x);
        else T =deleteNode(T, x);
    }
    travel(T);
return 0;
}

