#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "interface.h"

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
        default: return "?";
        }
}

int main (int argc, char** argv) {
        struct gameState G;
        struct gameState *p = &G;
        int gameSeed = atoi(argv[1]);

        srand(gameSeed);

        int k[10];

        int e = 0;

        selectKingdomCards(gameSeed, k);

        printf("\n");

        int playerNum = (rand() % 3) + 2;

        printf ("Starting game.\n");

        initializeGame(playerNum, k, gameSeed, p);

        printSupply(p);

        int money = 0;
        int cardPos[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
        int i = 0;
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

                printf("Player %d Card Obsession: %s\n", i, getCardName(k[cardFocus[i]]));
        }

        while (!isGameOver(p)) {
                for(i = 0; i < 10; i++) {
                        cardPos[i] = -1;
                }

                cardObsess = k[cardFocus[whoseTurn(p)]];

                money = countHandCoins(whoseTurn(p), p);

                if (cardPos[cardFocus[whoseTurn(p)]] != -1) {
                        printf("%d: %s played from position %d\n", whoseTurn(p),
                               getCardName(cardObsess),
                               cardPos[cardFocus[whoseTurn(p)]]);
                        playCard(cardPos[cardFocus[whoseTurn(p)]], -1, -1, -1, p);
                        printf("%s played.\n", getCardName(cardObsess));
                        printf("Player %d Gold: %d\n", e, money);
                }

                if (money >= 8) {
                        printf("%d: bought province\n", whoseTurn(p));
                        buyCard(province, p);
                } else if (money >= 6) {
                        printf("%d: bought gold\n", whoseTurn(p));
                        buyCard(gold, p);
                } else if ((money >= getCardCost(cardObsess))) {
                        printf("%d: bought %s\n", whoseTurn(p),
                               getCardName(cardObsess));
                        buyCard(cardObsess, p);
                } else if (money >= 3) {
                        printf("%d: bought silver\n", whoseTurn(p));
                        buyCard(silver, p);
                }

                printf("%d: end turn\n", whoseTurn(p));
                endTurn(p);


                printScores(p);

        }

        printf ("Finished game.\n");

        printScores(p);

        return 0;
}
