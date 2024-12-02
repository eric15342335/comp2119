/// @file 3036216734-C.cpp
/// @author Cheng Ho Ming, Eric
/// @brief
/// Implementation of a Treap (Tree + Heap) data structure supporting various operations
/// such as insertion, deletion, k-th element retrieval, position finding,
/// range sum, and range maximum queries.

#include <algorithm>
#include <climits>
#include <iostream>
#include <unordered_map>
using namespace std;

/// @struct TreapNode
/// @brief Represents a node in the Treap data structure.
struct TreapNode {
    public:
        long long value;                   ///< The value stored at this node.
        int subtreeSize;                   ///< Number of nodes in the subtree rooted at this node.
        long long subtreeSum;              ///< Sum of all values in the subtree.
        long long subtreeMax;              ///< Maximum value in the subtree.
        TreapNode *leftChild, *rightChild; ///< Pointers to the left and right child nodes.
        TreapNode * parentNode;            ///< Pointer to the parent node for backtracking.

        /// @brief Constructor to initialize a TreapNode with a given value.
        /// @param nodeValue The value to be stored in the node.
        TreapNode(long long nodeValue)
            : value(nodeValue), subtreeSize(1), subtreeSum(nodeValue), subtreeMax(nodeValue),
              leftChild(nullptr), rightChild(nullptr), parentNode(nullptr) {}
};

/// @brief Updates the metadata of a given node, including subtree size, sum, max value, and parent
/// pointers.
/// @param currentNode Pointer to the TreapNode to be updated.
void update(TreapNode * currentNode) {
    if (currentNode) {
        // Initialize with the node's own values.
        currentNode->subtreeSize = 1;
        currentNode->subtreeSum = currentNode->value;
        currentNode->subtreeMax = currentNode->value;

        // Update based on the left child.
        if (currentNode->leftChild) {
            currentNode->subtreeSize += currentNode->leftChild->subtreeSize;
            currentNode->subtreeSum += currentNode->leftChild->subtreeSum;
            currentNode->subtreeMax =
                max(currentNode->subtreeMax, currentNode->leftChild->subtreeMax);
            currentNode->leftChild->parentNode = currentNode;
        }

        // Update based on the right child.
        if (currentNode->rightChild) {
            currentNode->subtreeSize += currentNode->rightChild->subtreeSize;
            currentNode->subtreeSum += currentNode->rightChild->subtreeSum;
            currentNode->subtreeMax =
                max(currentNode->subtreeMax, currentNode->rightChild->subtreeMax);
            currentNode->rightChild->parentNode = currentNode;
        }
    }
}

/// @brief Splits the treap into two sub-treaps based on the key position.
///        The 'leftTreap' contains the first 'keyPosition' elements,
///        and the 'rightTreap' contains the remaining elements.
/// @param root The current root of the treap.
/// @param keyPosition The position at which to split the treap.
/// @param leftTreap Reference to the pointer that will point to the left sub-treap.
/// @param rightTreap Reference to the pointer that will point to the right sub-treap.
/// @param accumulatedPosition Auxiliary parameter to keep track of the current position during
/// recursion.
void split(TreapNode * root, int keyPosition, TreapNode *& leftTreap, TreapNode *& rightTreap,
    int accumulatedPosition = 0) {
    if (!root) {
        // If the root is null, both left and right treaps are null.
        leftTreap = rightTreap = nullptr;
    }
    else {
        // Calculate the current key based on the left subtree size.
        int currentKey =
            accumulatedPosition + (root->leftChild ? root->leftChild->subtreeSize : 0) + 1;
        if (keyPosition < currentKey) {
            // If the split key is in the left subtree, recursively split the left child.
            split(root->leftChild, keyPosition, leftTreap, root->leftChild, accumulatedPosition);
            // After splitting, set the current root as part of the right treap.
            rightTreap = root;
        }
        else {
            // If the split key is in the right subtree, recursively split the right child.
            split(root->rightChild, keyPosition, root->rightChild, rightTreap, currentKey);
            // After splitting, set the current root as part of the left treap.
            leftTreap = root;
        }
        // Update the current root's metadata after the split.
        update(root);
    }
}

/// @brief Merges two treaps into one while maintaining the treap properties.
/// @param rootReference Reference to the pointer that will point to the merged treap.
/// @param leftTreap Pointer to the left sub-treap.
/// @param rightTreap Pointer to the right sub-treap.
void merge(TreapNode *& rootReference, TreapNode * leftTreap, TreapNode * rightTreap) {
    if (!leftTreap || !rightTreap) {
        // If either left or right treap is null, the merged treap is the non-null treap.
        rootReference = leftTreap ? leftTreap : rightTreap;
    }
    else if (leftTreap->value > rightTreap->value) {
        // If the left treap's root value is greater, it becomes the new root.
        merge(leftTreap->rightChild, leftTreap->rightChild, rightTreap);
        rootReference = leftTreap;
    }
    else {
        // If the right treap's root value is greater or equal, it becomes the new root.
        merge(rightTreap->leftChild, leftTreap, rightTreap->leftChild);
        rootReference = rightTreap;
    }
    // Update the root's metadata after the merge.
    update(rootReference);
}

/// @brief Inserts a new node at a specified position within the treap.
/// @param rootReference Reference to the root of the treap.
/// @param insertionPosition The position at which to insert the new node.
/// @param newNode Pointer to the new TreapNode to be inserted.
void insert(TreapNode *& rootReference, int insertionPosition, TreapNode * newNode) {
    TreapNode *leftPart, *rightPart;
    // Split the treap into two parts: before and after the insertion position.
    split(rootReference, insertionPosition - 1, leftPart, rightPart);
    // Merge the left part with the new node.
    merge(leftPart, leftPart, newNode);
    // Merge the resulting treap with the right part.
    merge(rootReference, leftPart, rightPart);
}

/// @brief Removes the node at the specified position from the treap.
/// @param rootReference Reference to the root of the treap.
/// @param removalPosition The position of the node to be removed.
void removeKth(TreapNode *& rootReference, int removalPosition) {
    TreapNode *leftPart, *middlePart, *rightPart;
    // Split the treap to isolate the node at the desired position.
    split(rootReference, removalPosition - 1, leftPart, middlePart);
    split(middlePart, 1, middlePart, rightPart);
    // Merge the remaining treaps, effectively removing the target node.
    merge(rootReference, leftPart, rightPart);
    // Optionally, delete the removed node to free memory.
    delete middlePart;
}

/// @brief Retrieves the value of the node at the k-th position in the treap.
/// @param root Pointer to the root of the treap.
/// @param kthPosition The position of the desired node.
/// @return The value stored in the k-th node, or -1 if the treap is empty or k is out of bounds.
long long findKth(TreapNode * root, int kthPosition) {
    if (!root) {
        // If the treap is empty, return an invalid value.
        return -1; // Alternatively, handle as per requirements.
    }

    int leftSubtreeSize = root->leftChild ? root->leftChild->subtreeSize : 0;

    if (kthPosition == leftSubtreeSize + 1) {
        // If kthPosition matches the size of the left subtree + 1, current node is the k-th node.
        return root->value;
    }
    else if (kthPosition <= leftSubtreeSize) {
        // If kthPosition is within the left subtree, recurse on the left child.
        return findKth(root->leftChild, kthPosition);
    }
    else {
        // If kthPosition is in the right subtree, adjust kthPosition and recurse on the right
        // child.
        return findKth(root->rightChild, kthPosition - leftSubtreeSize - 1);
    }
}

/// @brief Calculates the current position (index) of a given node within the treap.
/// @param targetNode Pointer to the TreapNode whose position is to be found.
/// @return The 1-based index of the node in the treap.
int getIndex(TreapNode * targetNode) {
    int currentIndex = (targetNode->leftChild ? targetNode->leftChild->subtreeSize : 0) +
                       1; // Initialize with the size of the left subtree + 1.

    // Traverse up the treap using parent pointers.
    while (targetNode->parentNode) {
        if (targetNode->parentNode->rightChild == targetNode) {
            // If the current node is a right child, add the size of the left subtree of the parent
            // and the parent itself to the currentIndex.
            currentIndex +=
                (targetNode->parentNode->leftChild ? targetNode->parentNode->leftChild->subtreeSize
                                                   : 0) +
                1;
        }
        // Move up to the parent node.
        targetNode = targetNode->parentNode;
    }
    return currentIndex;
}

/// @brief Computes the sum of values from position l to r in the treap.
/// @param rootReference Reference to the root of the treap.
/// @param startPosition The starting position of the range.
/// @param endPosition The ending position of the range.
/// @return The sum of values within the specified range.
long long sumRange(TreapNode *& rootReference, int startPosition, int endPosition) {
    TreapNode *leftPart, *middlePart, *rightPart;
    // Split the treap to isolate the range [startPosition, endPosition].
    split(rootReference, startPosition - 1, leftPart, middlePart);
    split(middlePart, endPosition - startPosition + 1, middlePart, rightPart);
    // The sum is stored in the isolated middle treap.
    long long rangeSum = middlePart ? middlePart->subtreeSum : 0;
    // Merge the treaps back to restore the original treap structure.
    merge(middlePart, middlePart, rightPart);
    merge(rootReference, leftPart, middlePart);
    return rangeSum;
}

/// @brief Finds the maximum value within the range from position l to r in the treap.
/// @param rootReference Reference to the root of the treap.
/// @param startPosition The starting position of the range.
/// @param endPosition The ending position of the range.
/// @return The maximum value within the specified range, or LLONG_MIN if the range is invalid.
long long maxRange(TreapNode *& rootReference, int startPosition, int endPosition) {
    TreapNode *leftPart, *middlePart, *rightPart;
    // Split the treap to isolate the range [startPosition, endPosition].
    split(rootReference, startPosition - 1, leftPart, middlePart);
    split(middlePart, endPosition - startPosition + 1, middlePart, rightPart);
    // The maximum value is stored in the isolated middle treap.
    long long rangeMax = middlePart ? middlePart->subtreeMax : LLONG_MIN;
    // Merge the treaps back to restore the original treap structure.
    merge(middlePart, middlePart, rightPart);
    merge(rootReference, leftPart, middlePart);
    return rangeMax;
}

/// @brief Mapping from value to its corresponding treap node for quick access.
///        Assumes that all values are unique.
unordered_map<long long, TreapNode *> valueToNodeMap;

/// @brief The main function to execute the treap operations based on user input.
int main() {
    ios::sync_with_stdio(false); // Disable synchronization with C I/O for faster input/output.
    cin.tie(0);                  // Untie cin from cout for faster input/output.

    int numberOfElements, numberOfOperations;
    cin >> numberOfElements >>
        numberOfOperations; // Read the initial number of elements and the number of operations.

    TreapNode * treapRoot = nullptr; // Initialize the treap as empty.

    // Build the initial treap with 'numberOfElements' elements.
    for (int elementIndex = 1; elementIndex <= numberOfElements; elementIndex++) {
        long long elementValue;
        cin >> elementValue; // Read the value of the current element.
        TreapNode * newTreapNode =
            new TreapNode(elementValue); // Create a new TreapNode with the value.
        insert(
            treapRoot, elementIndex, newTreapNode);  // Insert the node at position 'elementIndex'.
        valueToNodeMap[elementValue] = newTreapNode; // Map the value to its node for quick access.
    }

    // Process 'numberOfOperations' operations.
    while (numberOfOperations--) {
        int operationCode;
        cin >> operationCode; // Read the operation code.
        if (operationCode == 1) {
            // Operation 1: Insert a new element.
            int insertionPosition;
            long long newValue;
            cin >> insertionPosition >> newValue; // Read the position and value to insert.
            TreapNode * newTreapNode = new TreapNode(newValue); // Create a new TreapNode.
            insert(treapRoot, insertionPosition,
                newTreapNode);                       // Insert the node at the specified position.
            valueToNodeMap[newValue] = newTreapNode; // Map the value to its node.
        }
        else if (operationCode == 2) {
            // Operation 2: Remove the k-th element.
            int removalPosition;
            cin >> removalPosition; // Read the position of the element to remove.
            // Find the value at the specified position.
            long long targetValue = findKth(treapRoot, removalPosition);
            valueToNodeMap.erase(targetValue);     // Remove the mapping for this value.
            removeKth(treapRoot, removalPosition); // Remove the node from the treap.
        }
        else if (operationCode == 3) {
            // Operation 3: Find the k-th element.
            int queryPosition;
            cin >> queryPosition; // Read the position to query.
            cout << findKth(treapRoot, queryPosition)
                 << '\n'; // Output the value at the specified position.
        }
        else if (operationCode == 4) {
            // Operation 4: Determine the position of a specific value.
            long long queryValue;
            cin >> queryValue; // Read the value to query.
            TreapNode * queriedNode =
                valueToNodeMap[queryValue];        // Retrieve the node associated with the value.
            int nodeIndex = getIndex(queriedNode); // Find the position of the node.
            cout << nodeIndex << '\n';             // Output the position.
        }
        else if (operationCode == 5) {
            // Operation 5: Calculate the sum of a range.
            int startPosition, endPosition;
            cin >> startPosition >> endPosition; // Read the start and end positions of the range.
            cout << sumRange(treapRoot, startPosition, endPosition)
                 << '\n'; // Output the sum of the range.
        }
        else if (operationCode == 6) {
            // Operation 6: Find the maximum value in a range.
            int startPosition, endPosition;
            cin >> startPosition >> endPosition; // Read the start and end positions of the range.
            cout << maxRange(treapRoot, startPosition, endPosition)
                 << '\n'; // Output the maximum value in the range.
        }
    }

    // Free memory by deleting all nodes in the treap.
    while (treapRoot != nullptr) {
        TreapNode * leftPart, * rightPart;
        split(treapRoot, 1, leftPart, rightPart); // Split the treap to isolate the root node.
        delete leftPart;                         // Delete the root node.
        treapRoot = rightPart;                    // Move to the next node.
    }

    return EXIT_SUCCESS; // Indicate successful execution.
}