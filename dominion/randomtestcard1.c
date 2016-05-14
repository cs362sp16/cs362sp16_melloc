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
                printf ("SMITHY TEST SUCCESSFULLY COMPLETED.\n");
        }
}

int main(int argc, char *argv[]) {
        srand(atoi(argv[1]));

        struct gameState g;

        int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
                     outpost,baron,tribute};

        int numPlayers = rand() % MAX_PLAYERS;
        int seed = atoi(argv[1]);

        initializeGame(numPlayers, k, seed, &g);

        g.deckCount[g.whoseTurn] = rand() % MAX_DECK;
        g.handCount[g.whoseTurn] = rand() % MAX_HAND;

        // int startingDeck = g.deckCount[g.whoseTurn];
        int startingHand = numHandCards(&g);

        myassert(cardEffect(smithy, 0, 0, 0, &g, 0, 0), "Smithy returned the wrong value.");

        myassert(numHandCards(&g) == startingHand + 3, "Wrong number of cards drawn by smithy.");

        checkasserts();
}
