/// @author Cheng Ho Ming, Eric (3036216734)
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node * left;
    Node * right;
    Node * parent;
    Node(int val) : key(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

Node * insert(Node * root, Node * newNode) {
    Node * parent = nullptr;
    Node * current = root;
    // go to the place that newNode should be
    while (current != nullptr) {
        parent = current;                // move downwards (parent would not be nullptr)
        if (newNode->key < current->key) // left is correct direction
            current = current->left;
        else
            current = current->right;
    }
    newNode->parent = parent;
    if (parent == nullptr)
        root = newNode;
    else if (newNode->key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;
    return root;
}

// Compute height and dhx, updates max_dhx
int computeHeight(Node * node, int & max_dhx) {
    if (node == nullptr)
        return -1; // As per the problem statement
    int left_height = computeHeight(node->left, max_dhx);
    int right_height = computeHeight(node->right, max_dhx);
    int dhx = std::abs(left_height - right_height);
    if (dhx > max_dhx)
        max_dhx = dhx;
    return 1 + std::max(left_height, right_height);
}

// facilitate -fsanitize=address debugging
void freeMemory(Node * node) {
    if (node == nullptr)
        return;
    freeMemory(node->left);
    freeMemory(node->right);
    delete node;
}

int main() {
    int n;
    cin >> n;
    vector<int> nodes(n);
    for (auto & each_node : nodes)
        cin >> each_node;

    Node * root = nullptr;
    for (auto each_node : nodes) {
        Node * z = new Node(each_node);
        root = insert(root, z);
    }

    int max_dhx = 0;
    computeHeight(root, max_dhx);
    cout << max_dhx;

    // free memory
    freeMemory(root);
}
