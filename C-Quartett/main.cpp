#include <stdio.h>
#include <stdlib.h>

// Card-Struktur, Dawid
typedef struct Card {
    int number;
    char name[50];
    int value1;
    double value2;
    struct Card* pNext;
} sCard;

sCard* CreateCardList(int);
void OutputList(sCard*);

int main() {
    sCard* pCardList = CreateCardList(10);
    OutputList(pCardList);
    system("pause");
    return 0;
}

// Karten-Liste erstellen, Dawid & Noah
sCard* CreateCardList(int cardCount) {
    sCard* pFirst = NULL;
    sCard* pLast = NULL;

    for (int el = 0; el < cardCount; el++) {
        sCard* pNew = (Card*)malloc(sizeof(sCard));
        pNew->number = el + 1;
        pNew->pNext = NULL;

        if (pFirst == NULL) pFirst = pNew;
        if (pLast != NULL) pLast->pNext = pNew;
        pLast = pNew;
    }
    return pFirst;
}

void OutputList(sCard* pFirst) {
    for (sCard* pOutput = pFirst; pOutput != NULL; pOutput++) {
        printf("Number: %i", pOutput->number);
        printf("------------------------------------------");
    }
}
