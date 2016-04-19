#include "cardEffects.h"
#include "dominion.h"
#include "dominion_helpers.h"

int baronEffect(struct gameState *state, int choice1) {
    return 0;
}
int stewardEffect(struct gameState *state, int handPos, int choice1, int choice2, int choice3) {
    return 0;
}
int ambassadorEffect(struct gameState *state, int handPos, int choice1, int choice2) {
    j = 0;		//used to check if player has enough cards to discard

    if (choice2 > 2 || choice2 < 0)
  {
    return -1;
  }

    if (choice1 == handPos)
  {
    return -1;
  }

    for (i = 0; i < state->handCount[currentPlayer]; i++)
  {
    if (i != handPos && i == state->hand[currentPlayer][choice1] && i != choice1)
      {
        j++;
      }
  }
    if (j < choice2)
  {
    return -1;
  }

    if (DEBUG)
  printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);

    //increase supply count for choosen card by amount being discarded
    state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;

    //each other player gains a copy of revealed card
    for (i = 0; i < state->numPlayers; i++)
  {
    if (i != currentPlayer)
      {
        gainCard(state->hand[currentPlayer][choice1], state, 0, i);
      }
  }

    //discard played card from hand
    discardCard(handPos, currentPlayer, state, 0);

    //trash copies of cards returned to supply
    for (j = 0; j < choice2; j++)
  {
    for (i = 0; i < state->handCount[currentPlayer]; i++)
      {
        if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1])
      {
        discardCard(i, currentPlayer, state, 1);
        break;
      }
      }
  }

    return 0;
}
int embargoEffect(struct gameState *state, int handPos, int choice1) {
    return 0;
}
int minionEffect(struct gameState *state, int handPos, int choice1, int choice2) {
    return 0;
}
