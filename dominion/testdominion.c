#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

const char* getCardName(enum CARD card)
{
        switch (card)
        {
        case adventurer: return "Adventurer";
        case council_room: return "Council Room";
        case feast: return "Feast";
        case gardens: return "Gardens";
        case mine: return "Mine";
        case remodel: return "Remodel";
        case smithy: return "Smithy";
        case village: return "Village";
        case baron: return "Baron";
        case great_hall: return "Great Hall";
        case minion: return "Minion";
        case steward: return "Steward";
        case tribute: return "Tribute";
        case ambassador: return "Ambassador";
        case cutpurse: return "Cutpurse";
        case embargo: return "Embargo";
        case outpost: return "Outpost";
        case salvager: return "Salvager";
        case sea_hag: return "Sea Hag";
        case treasure_map: return "Treasure Map";
        }
}

int main (int argc, char** argv) {
        struct gameState G;
        struct gameState *p = &G;
        int gameSeed = atoi(argv[1]);

        srand(gameSeed);

        int cards[20] = { adventurer, council_room, feast, gardens, mine,
                          remodel, smithy, village, baron, great_hall,
                          minion, steward, tribute, ambassador, cutpurse,
                          embargo, outpost, salvager, sea_hag, treasure_map };
        int cardsPicked[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        int k[10];
        int currentRand;
        int cardChosen;
        int e;

        for(int i = 0; i < 10; i++) {
                cardChosen = 0;

                while (cardChosen == 0) {
                        currentRand = rand() % 20;
                        if(cardsPicked[currentRand] == 0) {
                                k[i] = cards[currentRand];
                                printf("Card %d: %s\n", i + 1, getCardName(cards[currentRand]));
                                cardChosen = 1;
                                cardsPicked[currentRand] = 1;
                        }
                }
        }
        printf("\n");

        int playerNum = (rand() % 3) + 2;

        printf ("Starting game.\n");

        initializeGame(playerNum, k, gameSeed, p);

        int money = 0;
        int cardPos[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
        int i=0;
        int j;
        int sameCard;
        int cardIDontKnowAnymore;
        int pleaseKillMe;
        int cardFocus[4] = { 0, 0, 0, 0 };
        int cardObsess;

        for(i = 0; i < playerNum; i++) {
                pleaseKillMe = 0;
                sameCard = 0;
                cardIDontKnowAnymore = rand() % 10;
                if(i == 0) {
                        cardFocus[i] = cardIDontKnowAnymore;
                } else if(i == 1) {
                        while(cardIDontKnowAnymore == cardFocus[0]) {
                                cardIDontKnowAnymore = rand() % 10;
                        }
                        cardFocus[i] = cardIDontKnowAnymore;
                } else if(i == 2) {
                        while(cardIDontKnowAnymore == cardFocus[0]) {
                                cardIDontKnowAnymore = rand() % 10;
                        }
                        while(cardIDontKnowAnymore == cardFocus[1]) {
                                cardIDontKnowAnymore = rand() % 10;
                        }
                        cardFocus[i] = cardIDontKnowAnymore;
                } else if(i == 3) {
                        while(cardIDontKnowAnymore == cardFocus[0]) {
                                cardIDontKnowAnymore = rand() % 10;
                        }
                        while(cardIDontKnowAnymore == cardFocus[1]) {
                                cardIDontKnowAnymore = rand() % 10;
                        }
                        while(cardIDontKnowAnymore == cardFocus[2]) {
                                cardIDontKnowAnymore = rand() % 10;
                        }
                        cardFocus[i] = cardIDontKnowAnymore;
                }

                // printf("Player %d Card Obsession: %s\n", i, getCardName(k[cardFocus[i]]));
        }

        while (!isGameOver(p)) {
                money = 0;
                for(i = 0; i < 10; i++) {
                        cardPos[i] = -1;
                }

                cardObsess = k[cardFocus[whoseTurn(p)]];

                for (i = 0; i < numHandCards(p); i++) {
                        if (handCard(i, p) == copper)
                                money++;
                        else if (handCard(i, p) == silver)
                                money += 2;
                        else if (handCard(i, p) == gold)
                                money += 3;
                        for (j = 0; j < 10; j++ ) {
                                if (handCard(i, p) == k[j]) {
                                        cardPos[j] = i;
                                }
                        }
                }

                if (cardPos[cardFocus[whoseTurn(p)]] != -1) {
                        printf("%d: %s played from position %d\n", whoseTurn(p),
                               getCardName(cardObsess),
                               cardPos[cardFocus[whoseTurn(p)]]);
                        playCard(cardPos[cardFocus[whoseTurn(p)]], -1, -1, -1, p);
                        printf("%s played.\n", getCardName(cardObsess));
                        money = 0;
                        i=0;
                        while(i<numHandCards(p)) {
                                if (handCard(i, p) == copper) {
                                        playCard(i, -1, -1, -1, p);
                                        money++;
                                }
                                else if (handCard(i, p) == silver) {
                                        playCard(i, -1, -1, -1, p);
                                        money += 2;
                                }
                                else if (handCard(i, p) == gold) {
                                        playCard(i, -1, -1, -1, p);
                                        money += 3;
                                }
                                i++;
                        }
                        printf("Player %d Gold: %d\n", e, money);
                }

                if (money >= 8) {
                        printf("%d: bought province\n", whoseTurn(p));
                        buyCard(province, p);
                }
                else if (money >= 6) {
                        printf("%d: bought gold\n", whoseTurn(p));
                        buyCard(gold, p);
                }
                else if ((money >= 4)) { // && (numSmithies < 2)) {
                        printf("%d: bought %s\n", whoseTurn(p),
                               getCardName(cardObsess));
                        buyCard(cardObsess, p);
                        // numSmithies++;
                }
                else if (money >= 3) {
                        printf("%d: bought silver\n", whoseTurn(p));
                        buyCard(silver, p);
                }

                printf("%d: end turn\n", whoseTurn(p));
                endTurn(p);


                for(e = 0; e < playerNum; e++) {
                        printf("Player %d Score: %d\n", e, scoreFor(e, p));
                }

        }

        printf ("Finished game.\n");

        for(e = 0; e < playerNum; e++) {
                printf("Player %d: %d\n", e, scoreFor(e, p));
        }

        return 0;
}
