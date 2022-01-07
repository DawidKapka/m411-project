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

// Methode-Deklarationen
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

// Spiel starten und �berpr�fen, ob es neugestartet werden soll - Dawid
// R�ckgabetyp: Void
void Play() {
    bool playAgain = true;
    // Spiel wiederholen, solang playAgain == true ist.
    while (playAgain)
    {
        // Liste von 10 Karten erstellen und den Pointer auf die Erste in der pCardList Variable abspeichern.
        sCard* pCardList = CreateCardList(10);
        MixList(pCardList);
        StartGame(pCardList);
        char answer = '\0';
        bool answerWrong = true;
        // Nachfragen, solange nicht eine g�ltige Antwort eingegeben wird (y/n).
        while (answerWrong)
        {
            printf("\nWillst du nochmals spielen? (y/n)\n");
            scanf_s("%c", &answer);
            if (answer == 'y' || answer == 'n')
            {
                answerWrong = false;
                if (answer == 'n')
                {
                    // playAgain zu false setzen, damit das Spiel nicht mehr neugestartet wird.
                    playAgain = false;
                }
                else {
                    // Konsolenfenster bereinigen
                    system("@cls||clear");
                }
            }
            // Wiederholen, wenn antwort nicht ein 'y' oder 'n' ist.
            else {
                answerWrong = true;
                printf("\nUng\x81ltige Eingabe!\n");
            }
        }
        

    }

}

// Titeltext ausgeben - Dawid
// R�ckgabetyp: Void
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
// R�ckgabetyp: Void
void StartGame(sCard* pFirst) {
    int playerCards = 5;
    int pcCards = 5;
    short round = 1;
    // Die erste Karte in der Liste, welche dem Player geh�rt, in der pCurrentPlayerCard Variable abspeichern.
    sCard* pCurrentPlayerCard = GetNextCard(true, pFirst, pFirst);
    // Die erste Karte in der Liste, welche dem Pc geh�rt, in der pCurrentPcCard Variable abspeichern.
    sCard* pCurrentPcCard = GetNextCard(false, pFirst, pFirst);
    // Runde ausf�hren, solange der Player und der Pc beide mindestens 1 Karte besitzen.
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
        // �berpr�fen, ob ein g�ltiger Wert gespielt wurde (1/2)
        if (answer >= 0 && answer <= 2)
        {
            // �berpr�fen, ob der Player die Runde gewonnen hat.
            bool roundWon = ProcessAnswer(pCurrentPlayerCard, pCurrentPcCard, &answer);
            if (roundWon)
            {
                printf("\nDu hast diese Runde gewonnen!\n");
                // Letzte Karte vom Pc anzeigen.
                OutputPcCard(pCurrentPcCard);
                // Die zuletzt gespielte Karte vom Pc dem Player �bergeben.
                pCurrentPcCard->ownedByPlayer = true;
                pCurrentPlayerCard = pCurrentPlayerCard->pNext;
            }
            else {
                printf("\nDu hast diese Runde verloren!\n");
                // Letzte Karte vom Pc anzeigen.
                OutputPcCard(pCurrentPcCard);
                // Die zuletzt gespielte Karte vom Player dem Pc �bergeben.
                pCurrentPlayerCard->ownedByPlayer = false;
                pCurrentPcCard = pCurrentPcCard->pNext;
            }
            // Runde hochz�hlen.
            round++;
            // N�chste Karte vom Player bestimmen und die pCurrentPlayerCard Variable damit �berschreiben.
            pCurrentPlayerCard = GetNextCard(true, pFirst, pCurrentPlayerCard);
            // N�chste Karte vom Pc bestimmen und die pCurrentPcCard Variable damit �berschreiben.
            pCurrentPcCard = GetNextCard(false, pFirst, pCurrentPcCard);
            // �berpr�fen, ob der Player oder der Pc das Spiel gewonnen hat.
            bool gameEnded = CheckLoss(pCurrentPlayerCard, pCurrentPcCard);
            if (gameEnded)
            {
                // Spiel beenden, wenn jemand gewonnen hat.
                break;
            }
        }
        // Meldung ausgeben, falls ein ung�ltiger Wert gespielt wurde.
        else {
            printf("\nUng\x81ultige Eingabe!\n");
        }
        printf("\nKlicke Enter um weiterzuspielen...\n");
        // Warten, bis der Player eine Taste gedr�ckt hat.
        _getch();
        // Konsolenfenster bereinigen.
        system("@cls||clear");
    }
}

// Karte des Gegners am Schluss der Runde anzeigen - Noah
// R�ckgabetyp: Void
void OutputPcCard(sCard* pPc) {
    printf("\nKarte des Gegners:\n\n");
    OutputCardFormatted(pPc);
}

// �berpr�fen, ob Spieler oder PC verloren hat - Noah
// R�ckgabetyp: Boolean (true = spiel beendet; false = spiel nicht beendet)
bool CheckLoss(sCard* pPlayer, sCard* pPc) {
    // �berpr�fen, ob der Player verloren hat.
    if (pPlayer == NULL)
    {
        printf("\n\nGame Over! Du hast verloren! :(\n\n");
        // return true, falls das Spiel beendet werden soll.
        return true;
    }
    // �berpr�fen, ob der Pc verloren hat.
    else if (pPc == NULL)
    {
        printf("\n\nGratulation! Du hast gewonnen! :D\n\n");
        // return true, falls das Spiel beendet werden soll.
        return true;
    }
    return false;
}

// Werte vergleichen & auswerten - Dawid
// R�ckgabetyp: Boolean (true = runde gewonnen; false = runde verloren)
bool ProcessAnswer(sCard* pCurrentPlayerCard, sCard* pCurrentPcCard, int* answer) {
    bool roundWon = false;
    if (*answer == 1)
    {
        // roundWon auf true setzen, falls der erste Wert vom Player h�her ist als der erste Wert vom Pc.
        if (pCurrentPlayerCard->value1 > pCurrentPcCard->value1) roundWon = true;
    }
    else
    {
        // roundWon auf true setzen, falls der zweite Wert vom Player tiefer ist als der zweite Wert vom Pc.
        if (pCurrentPlayerCard->value2 < pCurrentPcCard->value2) roundWon = true;
    }
    return roundWon;
    
}
// Karte Formatiert in der Console ausgeben - Noah
// R�ckgabetyp: Void
void OutputCardFormatted(sCard* pCard) {
    printf("+-------------Auto-------------+\n");
    printf("| Name: ");
    puts(pCard->name);
    printf("| (1) Top Speed: %i\n", pCard->value1);
    printf("| (2) Fuel (l) / 100km: %1.2lf\n", pCard->value2);
    printf("+------------------------------+\n\n");
}

// Erste Karte vom PC bestimmen - Dawid
// R�ckgabetyp: sCard* (Pointer auf die n�chste Karte)
sCard* GetNextCard(bool isPlayer, sCard* pFirst, sCard* pCurrentCard) {
    bool secondRound = false;
    sCard* pCurrent = pCurrentCard;
    // for-loop h�chstens 11 mal wiederholen, damit es sicher durch jede Karte durchgeht.
    for (int i = 0; i <= 10; i++)
    {
        // Falls die momentane Karte und die n�chste Karte nicht == NULL sind, die momentane Karte mit der N�chsten Karte ersetzen
        if (pCurrent != NULL && pCurrent->pNext != NULL)
        {
            pCurrent = pCurrent->pNext;
        }
        // Sonst die momentane Karte mit der ersten Karte der Liste ersetzen
        else
        {
            pCurrent = pFirst;
        }

        // Falls der Besitzer der Karte mit der isPlayer Variable �bereinstimmt, die Karte zur�ckgeben.
        if (pCurrent->ownedByPlayer == isPlayer)
        {
            return pCurrent;
        }
    }
    // Falls keine Karten gefunden werden, die mit der isPlayer Variable �bereinstimmen, NULL zur�ckgeben. ( Spieler / Pc hat keine Karten mehr �brig)
    return NULL;
}

// Karten-Liste erstellen - Noah
// R�ckgabetyp: sCard* (Pointer auf die erste Karte der Kartenliste)
sCard* CreateCardList(int cardCount) {
    sCard* pFirst = NULL;
    sCard* pLast = NULL;

    // Namen der Karten in einem Array zusammenf�gen.
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
    // Werte f�r maximale Geschwindigkeit in einem Array zusammenf�gen.
    int maxSpeed[10] = {280, 240, 300, 369, 320, 345, 330, 350, 245, 220};
    // Werte f�r den Benzinverbrauch / Km in einem Array zusammenf�gen.
    double litersPerHundredKm[10] = { 11.69, 8.28, 14.86, 13.34, 15.72, 12.29, 0.00, 10.97, 6.94, 0.00};
 

    // Verkettete Liste erstellen und mit den entsprechenden Werten bef�llen.
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
// R�ckgabetyp: Void
void MixList(sCard* pFirst) {
    int randomNumber;
    // Durch jede Karte der Liste durchgehen.
    for (sCard* pTemp = pFirst; pTemp != NULL; pTemp = pTemp->pNext)
    {
        // Die tempor�re Karte pTemp mit einer anderer zuf�lliger Karte tauschen.
        SwapCard(pFirst, pTemp, rand() % 11);
    }
}

// 2 Karten Tauschen - Dawid
// R�ckgabetyp: Void
void SwapCard(sCard* pFirst, sCard* pSource, int number) {
    // neue, tempor�re Karte erstellen
    sCard* pTemp = (sCard*)malloc(sizeof(sCard));
    sCard* pCurrent = pFirst;
    // pCurrent mit der Karte ersetzen, die die gleiche Nummer hat, wie die number Variable-
    while (pCurrent && pCurrent->number != number)
    {
        pCurrent = pCurrent->pNext;
    }
    if (pCurrent)
    {
        // Die Werte der pCurrent Karte in die neue tempor�re pTemp Karte kopieren.
        pTemp->number = pCurrent->number;
        strcpy_s(pTemp->name, pCurrent->name);
        pTemp->value1 = pCurrent->value1;
        pTemp->value2 = pCurrent->value2;

        // Die Werte der pCurrent Karte mit den Werten der pSource Karte �berschreiben.
        pCurrent->number = pSource->number;
        strcpy_s(pCurrent->name, pSource->name);
        pCurrent->value1 = pSource->value1;
        pCurrent->value2 = pSource->value2;

        // Die Werte der pSource Karte mit den Werten der pTemp Karte, also den urspr�nglichen Werten der pTemp Karte �berschreiben. 
        pSource->number = pTemp->number;
        strcpy_s(pSource->name, pTemp->name);
        pSource->value1 = pTemp->value1;
        pSource->value2 = pTemp->value2;

        // Den Speicherplatz der pTemp Karte wieder leeren, da diese nicht mehr gebraucht wird.
        free(pTemp);
    }
}