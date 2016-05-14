#ifndef _CARD_EFFECTS_H
#define _CARD_EFFECTS_H

#include "dominion.h"
#include "dominion_helpers.h"

int baronEffect(struct gameState *state, int choice1);
int stewardEffect(struct gameState *state, int handPos, int choice1, int choice2, int choice3);
int ambassadorEffect(struct gameState *state, int handPos, int choice1, int choice2);
int embargoEffect(struct gameState *state, int handPos, int choice1);
int minionEffect(struct gameState *state, int handPos, int choice1, int choice2);
int smithyEffect(struct gameState *state, int handPos);

#endif
