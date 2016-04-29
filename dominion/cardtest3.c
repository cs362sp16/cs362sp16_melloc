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

  myassert(cardEffect(minion, 1, 0, 0, &g, 0, 0), "Minion returned the wrong value.");

  myassert(g.coins == startingCoins + 2, "Wrong number of coins gained by minion.");

  initializeGame(2, k, 5, &g);

  myassert(cardEffect(minion, 0, 1, 0, &g, 0, 0), "Minion returned the wrong value.");

  myassert(numHandCards(&g) == 4, "Wrong number of cards redrawn by minion.");

  checkasserts();
}
