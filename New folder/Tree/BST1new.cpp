#include <bits/stdc++.h>
#define forr(i,a,b) for(int i = a; i<=b; i++)
#define ll long long
using namespace std;
const ll N = 1e5+5;

int a[N];

struct Node{
    int data;
    Node *left;
    Node *right;
};


void insertNode(Node* &node, int newData){
    if (node == NULL){
        Node *newNode = new Node;
        newNode->data = newData;
        newNode->left = newNode->right = NULL;
        node = newNode;
    }
    else {
        if (newData < node->data) insertNode(node->left, newData);
        else insertNode(node->right, newData);
    }
}


void print(Node* node, string s)  {
	if (node != NULL) {
		forr(i,0,2) {
			if (s[i] == 'N') {
				cout << node->data << " ";
			}
			else if (s[i] == 'L') {
				print(node->left, s);
			}
			else if (s[i] == 'R') {
				print(node->right, s);
			}
		}
	}
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin>>n;
    forr(i,1,n) cin>>a[i];

    Node *root = new Node;

    root->data = a[1];
    root->left = root->right = NULL;
    forr(i,2,n) insertNode(root, a[i]);

    string s;
    cin>>s;
    print(root, s);


    return 0;
}

