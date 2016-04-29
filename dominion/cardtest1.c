#include "dominion.h"
#include "dominion_helpers.h"

int failed = 0;

int myassert(int b,char* msg) {
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

int main() {
  struct gameState g;

  int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};

  int r = initializeGame(2, k, 5, &g);

  startingHand = numHandCards(&g);

  myassert(cardEffect(smithy, 0, 0, 0, &g, 0, 0), "Smithy returned the wrong value.");

  myassert(numHandCards(&g) == startingHand + 2, "Wrong number of cards drawn by smithy.");

  checkasserts();
}
