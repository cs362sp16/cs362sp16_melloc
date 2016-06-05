#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>

int failed = 0;

void myassert(int b,char* msg) {
        if (b == 0) {
                printf("FAILED ASSERTION: %s\n",msg);
                failed = 1;
        }
}

void checkasserts() {
        if (!failed) {
                printf ("STEWARD TEST SUCCESSFULLY COMPLETED.\n");
        }
}

int main(int argc, char *argv[]) {
        srand(atoi(argv[1]));
        struct gameState g;

        int k[10] = {steward,adventurer,gardens,embargo,cutpurse,mine,ambassador,
                     outpost,baron,tribute};

        int numPlayers = rand() % MAX_PLAYERS;
        int seed = atoi(argv[1]);

        int numTests = 300;

        for(int i = 0; i < numTests; i++) {
                initializeGame(numPlayers, k, seed, &g);

                g.handCount[g.whoseTurn] = rand() % MAX_HAND;
                g.deckCount[g.whoseTurn] = rand() % MAX_DECK;
                while(g.deckCount[g.whoseTurn] < 2) {
                        g.deckCount[g.whoseTurn] = rand() % MAX_DECK;
                }

                int startingHand = numHandCards(&g);

                myassert(!cardEffect(steward, 1, 0, 0, &g, 0, 0), "Steward returned the wrong value.");

                myassert(numHandCards(&g) == startingHand + 1, "Wrong number of cards drawn by steward.");

                initializeGame(numPlayers, k, seed, &g);

                g.deckCount[g.whoseTurn] = rand() % MAX_DECK;
                g.handCount[g.whoseTurn] = rand() % MAX_HAND;

                int startingCoins = g.coins;

                myassert(!cardEffect(steward, 2, 0, 0, &g, 0, 0), "Steward returned the wrong value.");

                myassert(g.coins == startingCoins + 2, "Wrong number of coins gained by steward.");

                initializeGame(numPlayers, k, seed, &g);

                g.deckCount[g.whoseTurn] = rand() % MAX_DECK;
                g.handCount[g.whoseTurn] = rand() % MAX_HAND;

                startingHand = numHandCards(&g);

                myassert(!cardEffect(steward, 3, 1, 2, &g, 0, 0), "Steward returned the wrong value.");

                myassert(numHandCards(&g) == startingHand - 3, "Wrong number of cards discarded by steward.");

                seed++;
        }

        checkasserts();
}
