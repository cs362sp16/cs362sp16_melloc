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
                printf ("MINION TEST SUCCESSFULLY COMPLETED.\n");
        }
}

int main() {
        struct gameState g;

        int k[10] = {minion,adventurer,gardens,embargo,cutpurse,mine,ambassador,
                     outpost,baron,tribute};

        initializeGame(2, k, 5, &g);

        int startingCoins = g.coins;

        myassert(!cardEffect(minion, 1, 0, 0, &g, 0, 0), "Minion returned the wrong value.");

        myassert(g.coins == startingCoins + 2, "Wrong number of coins gained by minion.");

        initializeGame(4, k, 5, &g);

        for(int i = 0; i < 3; i++) {
                drawCard(1, &g);
        }
        for(int i = 0; i < 5; i++) {
                drawCard(2, &g);
        }
        for(int i = 0; i < 6; i++) {
                drawCard(3, &g);
        }

        int startingHands[4] = { g.handCount[0], g.handCount[1], g.handCount[2], g.handCount[3]};

        myassert(!cardEffect(minion, 0, 1, 0, &g, 0, 0), "Minion returned the wrong value.");

        for (int i = 0; i < g.numPlayers; i++)
        {
                if (i != g.whoseTurn)
                {
                        myassert(g.handCount[i] <= 4, "Minion did not discard other players' cards.");
                        if(startingHands[i] < 5) {
                                myassert(g.handCount[i] == startingHands[i], "Minion discarded too small of a hand.");
                        }
                }
        }

        myassert(numHandCards(&g) == 4, "Wrong number of cards redrawn by minion.");

        checkasserts();
}
