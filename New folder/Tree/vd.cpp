#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

typedef Node* Tree;

bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

void insertNode(Tree& root, int x) {
    if (root == nullptr) {
        root = new Node(x);
        return;
    }

    if (x < root->data) {
        insertNode(root->left, x);
    } else {
        insertNode(root->right, x);
    }
}

int countPrimes(Tree root) {
    if (root == nullptr) {
        return 0;
    }

    int count = isPrime(root->data) ? 1 : 0;
    count += countPrimes(root->left);
    count += countPrimes(root->right);

    return count;
}

bool searchElement(Tree root, int x) {
    if (root == nullptr) {
        return false;
    }

    if (root->data == x) {
        return true;
    } else if (x < root->data) {
        return searchElement(root->left, x);
    } else {
        return searchElement(root->right, x);
    }
}

int main() {


    int N, k, x;
    cin >> N;

    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    cin >> k;
    Tree root = nullptr;

    for (int i = 0; i < N; ++i) {
        insertNode(root, arr[i]);
    }

    if (k == 1) {
        int primeCount = countPrimes(root);
        cout << primeCount;
    } else if (k == 2) {
        cin>> x;
        bool exists = searchElement(root, x);
        cout << (exists ? "YES" : "NO");
    }

   

    return 0;
}

