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

int checkasserts() {
        if (!failed) {
                printf ("NUMHANDCARDS TEST SUCCESSFULLY COMPLETED.\n");
                return 0;
        }
        return 1;
}

int main() {
        struct gameState g;

        int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
                     outpost,baron,tribute};

        initializeGame(2, k, 5, &g);

        int actualHandCount = g.handCount[ whoseTurn(&g) ];

        myassert(numHandCards(&g) == actualHandCount, "numHandCount function returned the wrong value.");

        return checkasserts();
}
