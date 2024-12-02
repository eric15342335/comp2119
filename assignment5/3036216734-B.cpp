/// @author Cheng Ho Ming, Eric (3036216734)
#include <algorithm>
#include <iostream>
// type less "std::"
using namespace std;

struct AVLNode {
    long long key;
    AVLNode * left;  // smaller keys
    AVLNode * right; // larger keys
    int height;      // for ease of checking if the tree is balanced
    int size;        // Number of nodes in subtree
    long long sum;   // Sum of keys in subtree
    AVLNode(long long val)
        : key(val), left(nullptr), right(nullptr), height(1), size(1), sum(val) {}
};

// getter functions that checks null node
int getHeight(AVLNode * node) { return (node != nullptr) ? node->height : 0; }

// getter functions that checks null node
int getSize(AVLNode * node) { return (node != nullptr) ? node->size : 0; }

// getter functions that checks null node
long long getSum(AVLNode * node) { return (node != nullptr) ? node->sum : 0LL; }

// getter functions that checks null node
int getBalance(AVLNode * node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

/// update the node itself information e.g. @ref AVLNode::height, @ref AVLNode::size, @ref AVLNode::sum
void update(AVLNode * node) {
    // nullptr check
    if (node != nullptr) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        node->size = 1 + getSize(node->left) + getSize(node->right);
        node->sum = node->key + getSum(node->left) + getSum(node->right);
    }
}

// Right rotate, returns the new root
AVLNode * rightRotate(AVLNode * y) {
    AVLNode * x = y->left;
    AVLNode * T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights, sizes, and sums
    update(y);
    update(x);

    return x;
}

// Left rotate, return the new root
AVLNode * leftRotate(AVLNode * x) {
    AVLNode * y = x->right;
    AVLNode * T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights, sizes, and sums
    update(x);
    update(y);

    return y;
}

// Insert a key into the AVL tree
AVLNode * insertAVL(AVLNode * node, long long key) {
    if (node == nullptr) {
        return new AVLNode(key);
    }
    if (key < node->key) {
        node->left = insertAVL(node->left, key);
    }
    else {
        node->right = insertAVL(node->right, key);
    }

    update(node);

    int balance = getBalance(node);

    // Left Left Case: left subtree is higher, inserted at left subtree
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // Right Right Case: right subtree is higher, inserted at right subtree
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // Left Right Case: left subtree is higher, inserted at right subtree
    if (balance > 1 && key > node->left->key) {
        // double rotation
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case: right subtree is higher, inserted at left subtree
    if (balance < -1 && key < node->right->key) {
        // double rotation
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Find the node with minimum key value
AVLNode * minValueNode(AVLNode * node) {
    AVLNode * current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Delete a key from the AVL tree
AVLNode * deleteAVL(AVLNode * root, long long key) {
    if (root == nullptr) {
        return root;
    }
    if (key < root->key) {
        root->left = deleteAVL(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteAVL(root->right, key);
    }
    else {
        // Node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            AVLNode * temp = (root->left != nullptr) ? root->left : root->right;
            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else { // One child case
                *root = *temp;
            }
            delete temp;
        }
        else {
            // Node with two children: Get the inorder successor
            AVLNode * temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key);
        }
    }

    // If the tree had only one node
    if (root == nullptr) {
        return root;
    }

    // Update height, size, sum
    update(root);

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find k-th smallest element
long long findKth(AVLNode * root, int k) {
    if (root == nullptr) {
        return -1; // Should not happen if k is valid
    }
    int leftSize = getSize(root->left);
    if (k <= leftSize) {
        return findKth(root->left, k);
    }
    if (k == leftSize + 1) {
        return root->key;
    }
    return findKth(root->right, k - leftSize - 1);
}

// Find the index of x
int findIndex(AVLNode * root, long long x) {
    if (root == nullptr) {
        return 0; // Should not happen if x exists
    }
    if (x < root->key) {
        return findIndex(root->left, x);
    }
    if (x > root->key) {
        return getSize(root->left) + 1 + findIndex(root->right, x);
    }
    return getSize(root->left) + 1;
}

// Find the sum of first k elements
long long sumK(AVLNode * root, int k) {
    if ((root == nullptr) || k <= 0) {
        return 0;
    }
    if (getSize(root->left) >= k) {
        return sumK(root->left, k);
    }
    long long res = getSum(root->left) + root->key;
    if (k == getSize(root->left) + 1) {
        return res;
    }
    return res + sumK(root->right, k - getSize(root->left) - 1);
}

// Function to free the memory allocated for the BST
void freeMemory(AVLNode * node) {
    if (node == nullptr) {
        return;
    }
    freeMemory(node->left);
    freeMemory(node->right);
    delete node;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    AVLNode * root = nullptr;
    for (int i = 0; i < n; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            long long x;
            cin >> x;
            root = insertAVL(root, x);
        }
        else if (op == 2) {
            long long x;
            cin >> x;
            root = deleteAVL(root, x);
        }
        else if (op == 3) {
            int k;
            cin >> k;
            cout << findKth(root, k) << "\n";
        }
        else if (op == 4) {
            long long x;
            cin >> x;
            cout << findIndex(root, x) << "\n";
        }
        else if (op == 5) {
            int k;
            cin >> k;
            cout << sumK(root, k) << "\n";
        }
    }

    // free memory
    freeMemory(root);
}