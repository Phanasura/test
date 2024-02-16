#include <iostream>

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Tree {
private:
    Node* root;

    Node* insertNode(Node* node, int x) {
        if (node == nullptr) {
            return new Node(x);
        }

        if (x < node->data) {
            node->left = insertNode(node->left, x);
        } else if (x > node->data) {
            node->right = insertNode(node->right, x);
        }

        return node;
    }
    
    Node* findNode(Node* node, int x) const {
        if (node == nullptr || node->data == x) {
            return node;
        }

        if (x < node->data) {
            return findNode(node->left, x);
        } else {
            return findNode(node->right, x);
        }
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* node, int x) {
        if (node == nullptr) {
            return node;
        }

        if (x < node->data) {
            node->left = deleteNode(node->left, x);
        } else if (x > node->data) {
            node->right = deleteNode(node->right, x);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }

        return node;
    }

    bool searchNode(Node* node, int x) const {
        if (node == nullptr) {
            return false;
        }

        if (x == node->data) {
            return true;
        } else if (x < node->data) {
            return searchNode(node->left, x);
        } else {
            return searchNode(node->right, x);
        }
    }

    int sumNodes(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return node->data + sumNodes(node->left) + sumNodes(node->right);
    }

    int findMax(Node* node) const {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node->data;
    }

    int findMin(Node* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node->data;
    }
    
    int height(Node* node) const {
        if (node == nullptr) {
            return -1; // Height of an empty tree is -1
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return std::max(leftHeight, rightHeight) + 1;
    }

public:
    Tree() : root(nullptr) {}

    void insert(int x) {
        root = insertNode(root, x);
    }

    void remove(int x) {
        root = deleteNode(root, x);
    }

    bool search(int x) const {
        return searchNode(root, x);
    }

    int sum() const {
        return sumNodes(root);
    }

    int findMax() const {
        if (root == nullptr) {
            return -1; // Or any appropriate value to indicate an empty tree
        }
        return findMax(root);
    }

    int findMin() const {
        if (root == nullptr) {
            return -1; // Or any appropriate value to indicate an empty tree
        }
        return findMin(root);
    }
    int getHeight(int x) const {
        Node* node = findNode(root, x);
        if (node == nullptr) {
            return -1; // Node not found
        }

        return height(node);
    }
};

int main() {
    Tree myTree;

    myTree.insert(5);
    myTree.insert(3);
    myTree.insert(7);
    myTree.insert(2);
    myTree.insert(4);
    myTree.insert(6);
    myTree.insert(8);

//    std::cout << "Sum of tree nodes: " << myTree.sum() << std::endl;
//    std::cout << "Max value in tree: " << myTree.findMax() << std::endl;
//    std::cout << "Min value in tree: " << myTree.findMin() << std::endl;
//    std::cout << "Tree contains 4: " << (myTree.search(4) ? "Yes" : "No") << std::endl;
//    myTree.remove(3);
//
//    std::cout << "Tree contains 3 after removal: " << (myTree.search(3) ? "Yes" : "No") << std::endl;
    std::cout << "Height of node with value 5: " << myTree.getHeight(5) << std::endl;
    std::cout << "Height of node with value 2: " << myTree.getHeight(2) << std::endl;
    std::cout << "Height of node with value 8: " << myTree.getHeight(8) << std::endl;

    return 0;
}

