#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
using namespace std;
struct Node {
    int value;
    vector<Node*> neighbors;

    Node(int val) : value(val) {}
};
bool bidirectionalSearch(Node* source, Node* target) {
    queue<Node*> sourceQueue;
    unordered_set<Node*> sourceVisited;
    queue<Node*> targetQueue;
    unordered_set<Node*> targetVisited;
    sourceQueue.push(source);
    sourceVisited.insert(source);
    targetQueue.push(target);
    targetVisited.insert(target);
    while (!sourceQueue.empty() && !targetQueue.empty()) {
        int sourceSize = sourceQueue.size();
        for (int i = 0; i < sourceSize; ++i) {
            Node* current = sourceQueue.front();
            sourceQueue.pop();

            for (Node* neighbor : current->neighbors) {
                if (targetVisited.count(neighbor) > 0) {
                    return true;
                }
                if (sourceVisited.count(neighbor) == 0) {
                    sourceQueue.push(neighbor);
                    sourceVisited.insert(neighbor);
                }
            }
        }
        int targetSize = targetQueue.size();
        for (int i = 0; i < targetSize; ++i) {
            Node* current = targetQueue.front();
            targetQueue.pop();
            for (Node* neighbor : current->neighbors) {
                if (sourceVisited.count(neighbor) > 0) {
                    return true;
                }

                if (targetVisited.count(neighbor) == 0) {
                    targetQueue.push(neighbor);
                    targetVisited.insert(neighbor);
                }
            }
        }
    }
    return false;
}

int main() {
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    node1->neighbors = {node2};
    node2->neighbors = {node1, node3};
    node3->neighbors = {node2, node4};
    node4->neighbors = {node3};
    if (bidirectionalSearch(node1, node4)) {
        cout << "Ðu?ng di t?n t?i." << endl;
    } else {
        cout << "Không có du?ng di." << endl;
    }
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    return 0;
}

