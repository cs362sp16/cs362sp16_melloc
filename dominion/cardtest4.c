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
    printf ("VILLAGE TEST SUCCESSFULLY COMPLETED.\n");
  }
}

int main() {
  struct gameState g;

  int k[10] = {village,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};

  initializeGame(2, k, 5, &g);

  int startingHand = numHandCards(&g);
  int startingActions = g.numActions;

  myassert(!cardEffect(village, 0, 0, 0, &g, 0, 0), "Village returned the wrong value.");

  myassert(numHandCards(&g) == startingHand, "Wrong number of cards drawn by village.");

  myassert(g.numActions == startingActions + 2, "Wrong number of actions added by village.");

  checkasserts();
}
