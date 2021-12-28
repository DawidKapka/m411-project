#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ListLength 10;

// Card-Struktur - Dawid
typedef struct Card {
    int number;
    char name[50];
    int value1;
    double value2;
    struct Card* pNext;
} sCard;

sCard* CreateCardList(int);
void MixList(sCard*);
void SwapCard(sCard*, sCard*, int);
void StartGame(sCard*);
sCard* GetCurrentPcCard(sCard*, int);
void OutputCardFormatted(sCard*);
void OutputTitle();

int main() {
    srand(time(0));
    sCard* pCardList = CreateCardList(10);
    MixList(pCardList);
    StartGame(pCardList);
    system("pause");
    return 0;
}

// Titeltext ausgeben - Dawid
void OutputTitle() {
    printf("\n ________  ___  ___  ________  ________  _________  _______  _________  _________  \n");
    printf("|\\   __  \\|\\  \\|\\  \\|\\   __  \\|\\   __  \\|\\___   ___\\\\  ___ \\|\\___   ___\\\\___   ___\\ \n");
    printf("\\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\|\\  \\|___ \\  \\_\\ \\   __/\\|___ \\  \\_\\|___ \\  \\_| \n");
    printf(" \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\   __  \\ \\   _  _\\   \\ \\  \\ \\ \\  \\_|/__  \\ \\  \\     \\ \\  \\  \n");
    printf("  \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\ \\  \\ \\  \\\\  \\|   \\ \\  \\ \\ \\  \\_|\\ \\  \\ \\  \\     \\ \\  \\ \n");
    printf("   \\ \\_____  \\ \\_______\\ \\__\\ \\__\\ \\__\\\\ _\\    \\ \\__\\ \\ \\_______\\  \\ \\__\\     \\ \\__\\\n");
    printf("    \\|___| \\__\\|_______|\\|__|\\|__|\\|__|\\|__|    \\|__|  \\|_______|   \\|__|      \\|__|\n");
    printf("          \\|__|\n\n\n");
    printf("----------------------------------------------------------------------------------------\n\n\n");
}

// Spiel starten - Noah
void StartGame(sCard* pFirst) {
    int playerCards = 5;
    int pcCards = 5;
    short round = 1;
    sCard* pCurrentPlayerCard = pFirst;
    sCard* pCurrentPcCard = GetCurrentPcCard(pFirst, playerCards);
    OutputTitle();
    while (playerCards > 0 && pcCards > 0)
    {
        int playedValue = 1;
        int answer = 0;
        printf("************\n");
        printf("  Runde %i\n", round);
        printf("************\n\n");
        OutputCardFormatted(pCurrentPlayerCard);
        printf("Welchen Wert willst du spielen? (1/2): ");
        scanf_s("%i", &answer);
        if (answer >= 0 && answer <= 2)
        {
            printf("\nG\x81ltige Eingabe!\n");
            round++;
        }
        else {
            printf("\nUng\x81ultige Eingabe!\n");
        }
    }


}



// Karte Formatiert in der Console ausgeben - Dawid
void OutputCardFormatted(sCard* pCard) {
    printf("+--------Deine Karte--------+\n");
    printf("| Name: ");
    puts(pCard->name);
    printf("| Value 1: %i\n", pCard->value1);
    printf("| Value 2: %lf\n", pCard->value2);
    printf("+---------------------------+\n\n");
}

// Erste Karte vom PC bestimmen - Noah
sCard* GetCurrentPcCard(sCard* pFirst, int amount) {
    sCard* pCurrentPcCard = pFirst;
    for (int i = 0; i < amount; i++)
    {

        pCurrentPcCard = pCurrentPcCard->pNext;
    }
    return pCurrentPcCard;
}

// Karten-Liste erstellen - Noah
sCard* CreateCardList(int cardCount) {
    sCard* pFirst = NULL;
    sCard* pLast = NULL;

    for (int el = 0; el < cardCount; el++)
    {
        sCard* pNew = (sCard*)malloc(sizeof(sCard));
        pNew->number = el + 1;
        strcpy_s(pNew->name, "Test");
        pNew->value1 = 20;
        pNew->value2 = 10.0;
        pNew->pNext = NULL;
        if (pFirst == NULL) pFirst = pNew;
        if (pLast != NULL) pLast->pNext = pNew;
        pLast = pNew;
    }
    return pFirst;
}

// Kartenlisten mischeln - Dawid
void MixList(sCard* pFirst) {
    int randomNumber;
    for (sCard* pTemp = pFirst; pTemp != NULL; pTemp = pTemp->pNext)
    {
        SwapCard(pFirst, pTemp, rand() % 11);
    }
}

// 2 Karten Tauschen - Dawid
void SwapCard(sCard* pFirst, sCard* pSource, int number) {
    sCard* pTemp = (sCard*)malloc(sizeof(sCard));
    sCard* pCurrent = pFirst;
    while (pCurrent && pCurrent->number != number)
    {
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


