#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ListLength 10;

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
void MixList(sCard*);
void SwapCard(sCard*, sCard*, int);


int main() {
    srand(time(0));
    sCard* pCardList = CreateCardList(10);
    MixList(pCardList);
    OutputList(pCardList);
    system("pause");
    return 0;
}

// Karten-Liste erstellen, Dawid & Noah
sCard* CreateCardList(int cardCount) {
    sCard* pFirst = NULL;
    sCard* pLast = NULL;

    for (int el = 0; el < cardCount; el++) {
        sCard* pNew = (sCard*)malloc(sizeof(sCard));
        pNew->number = el + 1;
        pNew->pNext = NULL;
        if (pFirst == NULL) pFirst = pNew;
        if (pLast != NULL) pLast->pNext = pNew;
        pLast = pNew;
    }
    return pFirst;
}

void OutputList(sCard* pFirst) {
    for (sCard* pOutput = pFirst; pOutput != NULL; pOutput = pOutput->pNext)
    {
        printf("Number: %i", pOutput->number);
        printf("\n------------------------------------------\n");
    }
}

void MixList(sCard* pFirst) {
    int randomNumber;
    for (sCard* pTemp = pFirst; pTemp != NULL; pTemp = pTemp->pNext)
    {
        SwapCard(pFirst, pTemp, rand() % 11);
    }
}

void SwapCard(sCard* pFirst, sCard* pSource, int number) {
    sCard* pTemp = (sCard*)malloc(sizeof(sCard));
    sCard* pCurrent = pFirst;
    while (pCurrent && pCurrent->number != number) {
        pCurrent = pCurrent->pNext;
    }
    if (pCurrent)
    {
        pTemp->number = pCurrent->number;
        strcpy_s(pTemp->name, pCurrent->name);
        pTemp->value1 = pCurrent->value1;
        pTemp->value2 = pCurrent->value2;

        pCurrent->number = pSource->number;
        strcpy_s(pCurrent->name, pSource->name);
        pCurrent->value1 = pSource->value1;
        pCurrent->value2 = pSource->value2;

        pSource->number = pTemp->number;
        strcpy_s(pSource->name, pTemp->name);
        pSource->value1 = pTemp->value1;
        pSource->value2 = pTemp->value2;

    }
}


