#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};
typedef struct Node Node;

Node* mergeTwoSortedLinkedList(Node* first, Node* second) {
    if (first == NULL) return second;
    if (second == NULL) return first;
    if (first->data < second->data) {
        first->next = mergeTwoSortedLinkedList(first->next, second);
        return first;
    }
    else {
        second->next = mergeTwoSortedLinkedList(first, second->next);
        return second;
    }
}

#include <stdio.h>

int main() {
    // test
    Node* first = (Node*)malloc(sizeof(Node));
    Node* second = (Node*)malloc(sizeof(Node));
    first->data = 1;
    first->next = (Node*)malloc(sizeof(Node));
    first->next->data = 3;
    first->next->next = (Node*)malloc(sizeof(Node));
    first->next->next->data = 5;
    second->data = 2;
    second->next = (Node*)malloc(sizeof(Node));
    second->next->data = 4;
    second->next->next = (Node*)malloc(sizeof(Node));
    second->next->next->data = 6;
    Node* merged = mergeTwoSortedLinkedList(first, second);
    while (merged != NULL) {
        printf("%d ", merged->data);
        merged = merged->next;
    }
}