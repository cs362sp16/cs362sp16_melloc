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

int main() {
        struct gameState g;

        int k[10] = {steward,adventurer,gardens,embargo,cutpurse,mine,ambassador,
                     outpost,baron,tribute};

        initializeGame(2, k, 5, &g);

        int startingHand = numHandCards(&g);

        myassert(!(cardEffect(steward, 1, 0, 0, &g, 0, 0)), "Steward returned the wrong value.");

        myassert(numHandCards(&g) == startingHand + 1, "Wrong number of cards drawn by steward.");

        initializeGame(2, k, 5, &g);

        int startingCoins = g.coins;

        myassert(!(cardEffect(steward, 2, 0, 0, &g, 0, 0)), "Steward returned the wrong value.");

        myassert(g.coins == startingCoins + 2, "Wrong number of coins gained by steward.");

        initializeGame(2, k, 5, &g);

        startingHand = numHandCards(&g);

        myassert(!(cardEffect(steward, 3, 1, 2, &g, 0, 0)), "Steward returned the wrong value.");

        myassert(numHandCards(&g) == startingHand - 3, "Wrong number of cards discarded by steward.");

        checkasserts();
}
