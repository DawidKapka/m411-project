#include <stdio.h>

int main() {

    return 0;
}

typedef struct Card {
    char name[50];
    int value1;
    double value2;
    struct Card* pNext;
} Card;