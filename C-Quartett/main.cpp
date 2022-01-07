#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

#define ListLength 10;

// Card-Struktur - Dawid
typedef struct Card {
    int number;
    char name[50];
    int value1;
    double value2;
    struct Card* pNext;
    bool ownedByPlayer;
} sCard;

sCard* CreateCardList(int);
void MixList(sCard*);
void SwapCard(sCard*, sCard*, int);
void StartGame(sCard*);
sCard* GetNextCard(bool, sCard*, sCard*);
void OutputCardFormatted(sCard*);
void OutputTitle();
bool ProcessAnswer(sCard*, sCard*, int*);
bool CheckLoss(sCard*, sCard*);
char* GetNameArray();
void OutputPcCard(sCard*);
void Play();

int main() {
    srand(time(0));
    Play();
    system("pause");
    return 0;
}

// Spiel starten und überprüfen, ob es neugestartet werden soll - Dawid
void Play() {
    bool playAgain = true;
    while (playAgain)
    {
        sCard* pCardList = CreateCardList(10);
        MixList(pCardList);
        StartGame(pCardList);
        char answer = '\0';
        bool answerWrong = true;
        while (answerWrong)
        {
            printf("\nWillst du nochmals spielen? (y/n)\n");
            scanf_s("%c", &answer);
            if (answer == 'y' || answer == 'n')
            {
                answerWrong = false;
                if (answer == 'n')
                {
                    playAgain = false;
                }
                else {
                    system("@cls||clear");
                }
            }
            // wiederholen, wenn antwort nicht ein 'y' oder 'n' ist.
            else {
                answerWrong = true;
                printf("\nUng\x81ltige Eingabe!\n");
            }
        }
        

    }

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
    printf("                                                      by Noah Buchs & Dawid Kapka\n");
    printf("----------------------------------------------------------------------------------------\n\n\n");
}

// Spiel starten - Noah
void StartGame(sCard* pFirst) {
    int playerCards = 5;
    int pcCards = 5;
    short round = 1;
    sCard* pCurrentPlayerCard = GetNextCard(true, pFirst, pFirst);
    sCard* pCurrentPcCard = GetNextCard(false, pFirst, pFirst);
    while (playerCards > 0 && pcCards > 0)
    {
        OutputTitle();
        int playedValue = 1;
        int answer = 0;
        printf("************\n");
        printf("  Runde %i\n", round);
        printf("************\n\n");
        printf("Deine Karte:\n\n");
        OutputCardFormatted(pCurrentPlayerCard);
        printf("Welchen Wert willst du spielen? (1/2): ");
        scanf_s("%i", &answer);
        if (answer >= 0 && answer <= 2)
        {
            bool roundWon = ProcessAnswer(pCurrentPlayerCard, pCurrentPcCard, &answer);
            if (roundWon)
            {
                printf("\nDu hast diese Runde gewonnen!\n");
                OutputPcCard(pCurrentPcCard);
                pCurrentPcCard->ownedByPlayer = true;
                pCurrentPlayerCard = pCurrentPlayerCard->pNext;
            }
            else {
                printf("\nDu hast diese Runde verloren!\n");
                OutputPcCard(pCurrentPcCard);
                pCurrentPlayerCard->ownedByPlayer = false;
                pCurrentPcCard = pCurrentPcCard->pNext;
            }

            round++;
            pCurrentPlayerCard = GetNextCard(true, pFirst, pCurrentPlayerCard);
            pCurrentPcCard = GetNextCard(false, pFirst, pCurrentPcCard);
            bool gameEnded = CheckLoss(pCurrentPlayerCard, pCurrentPcCard);
            if (gameEnded)
            {
                break;
            }
        }
        else {
            printf("\nUng\x81ultige Eingabe!\n");
        }
        printf("\nKlicke Enter um weiterzuspielen...\n");
        _getch();
        system("@cls||clear");
    }
}

// Karte des Gegners am Schluss der Runde anzeigen - Noah
void OutputPcCard(sCard* pPc) {
    printf("\nKarte des Gegners:\n\n");
    OutputCardFormatted(pPc);
}

// Überprüfen, ob Spieler oder PC verloren hat - Noah
bool CheckLoss(sCard* pPlayer, sCard* pPc) {
    if (pPlayer == NULL)
    {
        printf("\n\nGame Over! Du hast verloren! :(\n\n");
        return true;
    }
    else if (pPc == NULL)
    {
        printf("\n\nGratulation! Du hast gewonnen! :D\n\n");
        return true;
    }
    return false;
}

// Werte vergleichen & auswerten - Dawid
bool ProcessAnswer(sCard* pCurrentPlayerCard, sCard* pCurrentPcCard, int* answer) {
    bool roundWon = false;
    if (*answer == 1)
    {
        if (pCurrentPlayerCard->value1 > pCurrentPcCard->value1) roundWon = true;
    }
    else
    {
        if (pCurrentPlayerCard->value2 < pCurrentPcCard->value2) roundWon = true;
    }
    return roundWon;
    
}
// Karte Formatiert in der Console ausgeben - Dawid
void OutputCardFormatted(sCard* pCard) {
    printf("+-------------Auto-------------+\n");
    printf("| Name: ");
    puts(pCard->name);
    printf("| (1) Top Speed: %i\n", pCard->value1);
    printf("| (2) Fuel (l) / 100km: %1.2lf\n", pCard->value2);
    printf("+------------------------------+\n\n");
}

// Erste Karte vom PC bestimmen - Noah
sCard* GetNextCard(bool isPlayer, sCard* pFirst, sCard* pCurrentCard) {
    bool secondRound = false;
    sCard* pCurrent = pCurrentCard;
    for (int i = 0; i < 20; i++)
    {
        if (pCurrent != NULL && pCurrent->pNext != NULL)
        {
            pCurrent = pCurrent->pNext;
        }
        else
        {
            pCurrent = pFirst;
        }

        if (pCurrent->ownedByPlayer == isPlayer)
        {
            return pCurrent;
        }
    }
    return NULL;
}

// Karten-Liste erstellen - Noah
sCard* CreateCardList(int cardCount) {
    sCard* pFirst = NULL;
    sCard* pLast = NULL;

    char names[10][50] = {
    "Honda Civic TCR",
    "Skoda Octavia",
    "BMW i8",
    "Lamborghini Aventador",
    "Subaru WRX STI",
    "Bugatti Divo",
    "Tesla Model S",
    "Audi R8 V10",
    "Volkswagen Golf GTI R5",
    "Tesla Cybertruck"
    };

    int maxSpeed[10] = {280, 240, 300, 369, 320, 345, 330, 350, 245, 220};
    double litersPerHundredKm[10] = { 11.69, 8.28, 14.86, 13.34, 15.72, 12.29, 0.00, 10.97, 6.94, 0.00};
 

    for (int el = 0; el < cardCount; el++)
    {
        sCard* pNew = (sCard*)malloc(sizeof(sCard));
        pNew->number = el + 1;
        strcpy_s(pNew->name, names[el]);
        pNew->value1 = maxSpeed[el];
        pNew->value2 = litersPerHundredKm[el];
        pNew->ownedByPlayer = (el + 1) % 2 == 0;
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