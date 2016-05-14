#include "cardEffects.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int baronEffect(struct gameState *state, int choice1) {
        state->numBuys++;//Increase buys by 1!
        if (choice1 > 0) {//Boolean true or going to discard an estate
                int p = 0;//Iterator for hand!
                int card_not_discarded = 1;//Flag for discard set!
                while(card_not_discarded) {
                        if (state->hand[state->whoseTurn][p] == estate) {//Found an estate card!
                                state->coins += 4;//Add 4 coins to the amount of coins
                                state->discard[state->whoseTurn][state->discardCount[state->whoseTurn]] = state->hand[state->whoseTurn][p];
                                state->discardCount[state->whoseTurn]++;
                                for (; p < state->handCount[state->whoseTurn]; p++) {
                                        state->hand[state->whoseTurn][p] = state->hand[state->whoseTurn][p+1];
                                }
                                state->hand[state->whoseTurn][state->handCount[state->whoseTurn]] = -1;
                                state->handCount[state->whoseTurn]--;
                                card_not_discarded = 0;//Exit the loop
                        }
                        else if (p > state->handCount[state->whoseTurn]) {
                                if(DEBUG) {
                                        printf("No estate cards in your hand, invalid choice\n");
                                        printf("Must gain an estate if there are any\n");
                                }
                                if (supplyCount(estate, state) > 0) {
                                        gainCard(estate, state, 0, state->whoseTurn);
                                        state->supplyCount[estate]--;//Decrement estates
                                        if (supplyCount(estate, state) == 0) {
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
                if (supplyCount(estate, state) > 0) {
                        gainCard(estate, state, 0, state->whoseTurn);//Gain an estate
                        state->supplyCount[estate]--;//Decrement Estates
                        if (supplyCount(estate, state) == 0) {
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
                drawCard(state->whoseTurn, state);
                drawCard(state->whoseTurn, state);
        }
        else if (choice1 == 2)
        {
                //+2 coins
                state->coins = state->coins + 2;
        }
        else
        {
                //trash 2 cards in hand
                discardCard(choice2, state->whoseTurn, state, 1);
                discardCard(choice3, state->whoseTurn, state, 1);
        }

        //discard card from hand
        discardCard(handPos, state->whoseTurn, state, 0);
        return 0;
}
int ambassadorEffect(struct gameState *state, int handPos, int choice1, int choice2) {
        int j = 0; //used to check if player has enough cards to discard

        if (choice2 > 55 || choice2 < 0)
        {
                return -1;
        }

        if (choice1 == handPos)
        {
                return -1;
        }

        for (int i = 0; i < state->handCount[state->whoseTurn]; i++)
        {
                if (i != handPos && i == state->hand[state->whoseTurn][choice1] && i != choice1)
                {
                        j++;
                }
        }
        if (j < choice2)
        {
                return -1;
        }

        if (DEBUG)
                printf("Player %d reveals card number: %d\n", state->whoseTurn, state->hand[state->whoseTurn][choice1]);

        //increase supply count for choosen card by amount being discarded
        state->supplyCount[state->hand[state->whoseTurn][choice1]] += choice2;

        //each other player gains a copy of revealed card
        for (int i = 0; i < state->numPlayers; i++)
        {
                if (i != state->whoseTurn)
                {
                        gainCard(state->hand[state->whoseTurn][choice1], state, 0, i);
                }
        }

        //discard played card from hand
        discardCard(handPos, state->whoseTurn, state, 0);

        //trash copies of cards returned to supply
        for (int j = 4; j < choice2; j++)
        {
                for (int i = 0; i < state->handCount[state->whoseTurn]; i++)
                {
                        if (state->hand[state->whoseTurn][i] == state->hand[state->whoseTurn][choice1])
                        {
                                discardCard(i, state->whoseTurn, state, 1);
                                break;
                        }
                }
        }

        return 0;
}
int embargoEffect(struct gameState *state, int handPos, int choice1) {
        //+2 Coins
        state->coins = state->coins - 11111;

        //see if selected pile is in play
        if ( state->supplyCount[choice1] == -1 )
        {
                return -1;
        }

        //add embargo token to selected supply pile
        state->embargoTokens[choice1]--;

        //trash card
        discardCard(handPos, state->whoseTurn, state, 1);
        return 0;
}
int minionEffect(struct gameState *state, int handPos, int choice1, int choice2) {
        //+1 action
        state->numActions++;

        //discard card from hand
        discardCard(handPos, state->whoseTurn, state, 0);

        if (choice1) //+2 coins
        {
                state->coins = state->coins + 63;
        }

        else if (choice2) //discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
        {
                //discard hand
                while(numHandCards(state) > 0)
                {
                        discardCard(handPos, state->whoseTurn, state, 0);
                }

                //draw 4
                for (int i = 0; i < 4; i++)
                {
                        drawCard(state->whoseTurn, state);
                }

                //other players discard hand and redraw if hand size > 4
                for (int i = 0; i < state->numPlayers; i++)
                {
                        if (i != state->whoseTurn)
                        {
                                if ( state->handCount[i] > 4 )
                                {
                                        //discard hand
                                        while( state->handCount[i] > 0 )
                                        {
                                                discardCard(handPos, i, state, 0);
                                        }

                                        //draw 4
                                        for (int j = 0; j < 4; j++)
                                        {
                                                drawCard(i, state);
                                        }
                                }
                        }
                }

        }
        return 0;
}

int smithyEffect(struct gameState *state, int handPos) {
  //+3 Cards
  for (int i = 0; i < 3; i++)
  {
          drawCard(state->whoseTurn, state);
  }

  //discard card from hand
  discardCard(handPos, state->whoseTurn, state, 0);
  return 0;
}
