#include <iostream>
#include <string>

struct TreeNode {
    std::string word;
    std::string meaning;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(std::string w, std::string m) {
        word = w;
        meaning = m;
        left = nullptr;
        right = nullptr;
    }
};

class Dictionary {
private:
    TreeNode* root;

public:
    Dictionary() {
        root = nullptr;
    }

    void insert(std::string word, std::string meaning) {
        root = insertRecursive(root, word, meaning);
    }

    TreeNode* insertRecursive(TreeNode* node, std::string word, std::string meaning) {
        if (node == nullptr) {
            return new TreeNode(word, meaning);
        }

        if (word < node->word) {
            node->left = insertRecursive(node->left, word, meaning);
        } else if (word > node->word) {
            node->right = insertRecursive(node->right, word, meaning);
        }

        return node;
    }

    std::string search(std::string word) {
        return searchRecursive(root, word);
    }

    std::string searchRecursive(TreeNode* node, std::string word) {
        if (node == nullptr) {
            return "Word not found.";
        }

        if (word == node->word) {
            return node->meaning;
        } else if (word < node->word) {
            return searchRecursive(node->left, word);
        } else {
            return searchRecursive(node->right, word);
        }
    }
};

int main() {
    Dictionary dict;
    dict.insert("apple", "A fruit.");
    dict.insert("banana", "A yellow fruit.");
    dict.insert("cat", "A furry animal.");

    std::string wordToSearch = "banana";
    std::string meaning = dict.search(wordToSearch);
    std::cout << "Meaning of '" << wordToSearch << "': " << meaning << std::endl;

    return 0;
}

