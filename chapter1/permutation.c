#include <stdio.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permutation(char *characters, int start, int end) {
    if (start == end) {
        for (int i = 0; i <= end; i++) {
            printf("%c", characters[i]);
        }
        printf("\n");
    } else {
        for (int i = start; i <= end; i++) {
            swap(&characters[start], &characters[i]);
            permutation(characters, start + 1, end);
            swap(&characters[start], &characters[i]);
        }
    }
}

int main() {
    char characters[] = {'a', 'b', 'c'};
    permutation(characters, 0, sizeof(characters) / sizeof(characters[0]) - 1);
    return 0;
}
