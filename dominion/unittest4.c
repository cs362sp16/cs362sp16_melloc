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
    printf ("ISGAMEOVER TEST SUCCESSFULLY COMPLETED.\n");
  }
}

int main() {
  struct gameState g;

  int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
	       outpost,baron,tribute};

  initializeGame(2, k, 5, &g);

  myassert(!isGameOver(&g), "isGameOver returned game over on start.");

  g.supplyCount[province] = 0;

  myassert(isGameOver(&g), "isGameOver didn't account for 0 provinces");

  g.supplyCount[province] = 1;

  g.supplyCount[0] = 0;
  g.supplyCount[1] = 0;
  g.supplyCount[2] = 0;

  myassert(isGameOver(&g), "isGameOver didn't account for 3 empty supply decks");

  checkasserts();
}
