#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};
typedef struct Node Node;

Node* getCycleBeginsPtr(Node* head) {
    if (head == NULL) return NULL;
    Node* one_step = head;
    Node* two_step = head;
    while (two_step != NULL && two_step->next != NULL) {
        one_step = one_step->next;
        two_step = two_step->next->next;
        if (one_step == two_step) {
            Node* cycle_begins = head;
            while (cycle_begins != one_step) {
                cycle_begins = cycle_begins->next;
                one_step = one_step->next;
            }
            return cycle_begins;
        }
    }
    return NULL;
}
