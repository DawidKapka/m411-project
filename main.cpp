#include <stdio.h>

int main() {
    Card* pCardList = CreateCardList(10);
    return 0;
}

// Card-Struktur, Dawid
typedef struct Card {
    int number;
    char name[50];
    int value1;
    double value2;
    struct Card* pNext;
} Card;

// Karten-Liste erstellen, Dawid
Card* CreateCardList(int cardCount) {
    Card* pFirst = NULL;
    Card* pNext = NULL;

    for(int el = 0; el < cardCount; el++) {
        Card* pNew = (Card*)malloc(sizeof(Card));
        pNew->number = el + 1;
        pNew->pNext = NULL;

        if (pFirst == NULL) pFirst = pNew;
        if (pLast != NULL) pLast->pNext = pNew;
        pLast = pNew;
    }
    return pFirst;
}

