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
                printf ("WHOSETURN TEST SUCCESSFULLY COMPLETED.\n");
        }
}

int main() {
        struct gameState g;

        int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
                     outpost,baron,tribute};

        initializeGame(2, k, 5, &g);

        int actualWhoseTurn = g.whoseTurn;

        myassert(whoseTurn(&g) == actualWhoseTurn, "whoseTurn function returned the wrong value.");

        checkasserts();
}
