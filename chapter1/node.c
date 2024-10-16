#include <stdlib.h>
#include <stdio.h>
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr next;
};
typedef node_ptr list;
list T;

int main() {
    T = malloc(sizeof(struct node));
    //T = malloc(sizeof(node_ptr*)); // same as above, as node_ptr is a pointer by default
    printf("%p\n", T);
}
