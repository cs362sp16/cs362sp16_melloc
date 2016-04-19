#include "cardEffects.h"
#include "dominion.h"
#include "dominion_helpers.h"

int baronEffect(struct gameState *state, int choice1) {
    state->numBuys++;//Increase buys by 1!
    if (choice1 > 0){//Boolean true or going to discard an estate
  int p = 0;//Iterator for hand!
  int card_not_discarded = 1;//Flag for discard set!
  while(card_not_discarded){
    if (state->hand[currentPlayer][p] == estate){//Found an estate card!
      state->coins += 4;//Add 4 coins to the amount of coins
      state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
      state->discardCount[currentPlayer]++;
      for (;p < state->handCount[currentPlayer]; p++){
        state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
      }
      state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
      state->handCount[currentPlayer]--;
      card_not_discarded = 0;//Exit the loop
    }
    else if (p > state->handCount[currentPlayer]){
      if(DEBUG) {
        printf("No estate cards in your hand, invalid choice\n");
        printf("Must gain an estate if there are any\n");
      }
      if (supplyCount(estate, state) > 0){
        gainCard(estate, state, 0, currentPlayer);
        state->supplyCount[estate]--;//Decrement estates
        if (supplyCount(estate, state) == 0){
      isGameOver(state);
        }
      }
      card_not_discarded = 0;//Exit the loop
    }

    else{
      p++;//Next card
    }
  }
    }

    else{
  if (supplyCount(estate, state) > 0){
    gainCard(estate, state, 0, currentPlayer);//Gain an estate
    state->supplyCount[estate]--;//Decrement Estates
    if (supplyCount(estate, state) == 0){
      isGameOver(state);
    }
  }
    }


    return 0;
}
int stewardEffect(struct gameState *state, int handPos, int choice1, int choice2, int choice3) {
    if (choice1 == 1)
  {
    //+2 cards
    drawCard(currentPlayer, state);
    drawCard(currentPlayer, state);
  }
    else if (choice1 == 2)
  {
    //+2 coins
    state->coins = state->coins + 2;
  }
    else
  {
    //trash 2 cards in hand
    discardCard(choice2, currentPlayer, state, 1);
    discardCard(choice3, currentPlayer, state, 1);
  }

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
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
    //+2 Coins
    state->coins = state->coins + 2;

    //see if selected pile is in play
    if ( state->supplyCount[choice1] == -1 )
  {
    return -1;
  }

    //add embargo token to selected supply pile
    state->embargoTokens[choice1]++;

    //trash card
    discardCard(handPos, currentPlayer, state, 1);
    return 0;

  case outpost:
    //set outpost flag
    state->outpostPlayed++;

    //discard card
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}
int minionEffect(struct gameState *state, int handPos, int choice1, int choice2) {
    //+1 action
    state->numActions++;

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    if (choice1)		//+2 coins
  {
    state->coins = state->coins + 2;
  }

    else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
  {
    //discard hand
    while(numHandCards(state) > 0)
      {
        discardCard(handPos, currentPlayer, state, 0);
      }

    //draw 4
    for (i = 0; i < 4; i++)
      {
        drawCard(currentPlayer, state);
      }

    //other players discard hand and redraw if hand size > 4
    for (i = 0; i < state->numPlayers; i++)
      {
        if (i != currentPlayer)
      {
        if ( state->handCount[i] > 4 )
          {
            //discard hand
            while( state->handCount[i] > 0 )
          {
            discardCard(handPos, i, state, 0);
          }

            //draw 4
            for (j = 0; j < 4; j++)
          {
            drawCard(i, state);
          }
          }
      }
      }

  }
    return 0;
}
