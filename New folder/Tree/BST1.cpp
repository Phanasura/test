#include <bits/stdc++.h>
#define INF int64_t(1e9)
#define pii pair <int, int>
#define pll pair <long long, long long>
#define file "bst1"
using namespace std;
const int nmax=2e5 + 5;
const int MOD = 1e9 + 7;
struct Node
{
    int data;
    Node *Left;
    Node *Right;
};
typedef struct Node *Tree;

//void BTree_Init(Tree *Root)
//{
//    (*Root) = NULL;
//}
//Node *CreateNode(int NewData)
//{
//    Node *p;
//    p = (Node*)malloc(sizeof (struct Node));
//    if (p!=NULL)
//    {
//        p -> Left = NULL;
//        p -> Right = NULL;
//        p -> data = NewData;
//    }
//    return p;
//}
void Insert_node(Tree &T, int x)
{
    if (T == NULL )
    {
        Node *p = new Node;
        p -> data = x;
        p -> Left = NULL;
        p -> Right = NULL;
        T = p;
    }
    else
    {
        if (x < T->data) Insert_node(T->Left, x);
        else Insert_node(T->Right, x);
    }
}
//void addLeft(int x, Tree Root)
//{
//    Tree LPtr;
//    if (Root == NULL) Root = CreateNode(x);
//    else
//    {
//        LPtr = Root;
//        while (LPtr -> Left != NULL) LPtr = LPtr -> Left;
//        LPtr -> Left = CreateNode(x);
//    }
//}
//void addRight(int x, Tree Root)
//{
//    Tree RPtr;
//    if (Root = NULL) Root = CreateNode(x);
//    else
//    {
//        RPtr = Root;
//        while (RPtr -> Right != NULL) RPtr = RPtr -> Right;
//        RPtr -> Right = CreateNode(x);
//    }
//}
void NLR(Tree t)
{
    if (t!=NULL)
    {
        cout << t->data << " ";
        NLR(t->Left);
        NLR(t->Right);
    }
}
void LNR(Tree t)
{
    if (t!=NULL)
    {
        LNR(t->Left);
        cout << t->data << " ";
        LNR(t->Right);
    }
}
void LRN(Tree t)
{
    if (t!=NULL)
    {
        LRN(t->Left);
        LRN(t->Right);
        cout << t->data << " ";
    }
}
void NRL(Tree t)
{
    if (t!=NULL)
    {
        cout << t->data << " ";
        NRL(t->Right);
        NRL(t->Left);
    }
}
void RNL(Tree t)
{
    if (t!=NULL)
    {
        RNL(t->Right);
        cout << t->data << " ";
        RNL(t->Left);
    }
}
void RLN(Tree t)
{
    if (t!=NULL)
    {
        RLN(t->Right);
        RLN(t->Left);
        cout << t->data << " ";
    }
}
int n;
int a[nmax];
Tree T;
int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    //freopen(file".inp","r",stdin);
    //freopen(file".out","w",stdout);
    cin >> n;
    for (int i=1;i<=n;i++) cin >> a[i];
    //BTree_Init(*T);
    for (int i=1;i<=n;i++) Insert_node(T,a[i]);
//    NLR(T);
string t;
    cin >> t;
    if(t == "NLR") NLR(T);
    else if (t == "LNR") LNR(T);
    else if (t == "LRN") LRN(T);
    else if (t == "NRL") NRL(T);
    else if (t == "RNL") RNL(T);
    else if (t == "RLN") RLN(T);
return 0;
}

