/*********************************************************************
** Program name: unittest1.c
** Author: Nathan Zimmerman
** Date: 02/04/2018
** Description: 
 What the program does: 
how to run it:
*********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1B[33m"
#define RESET   "\x1b[0m"

void assertTest(int testCase) {
  if (testCase) {
    printf(GREEN "PASS" RESET "\n");
  } else {
    printf(RED "FAIL" RESET "\n");
  }
}

int main() {
	int seed = 1000;
  int numPlayers = 2;
  int player;
  int card = -1;
  int cardCount;
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
               village, baron, great_hall};
  
  struct gameState game, testGame;

  printf("-- Testing fullDeckCount() -- \n\n");
  for (player = 0; player < numPlayers; player++) {
    printf("-- Player = %d --\n", player);

    printf(YELLOW "Test card not in deck.\n" RESET);
    memset(&game, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &game);
    memcpy(&testGame, &game, sizeof(struct gameState));

    cardCount = fullDeckCount(player, card, &testGame);
    printf("Deck count: %d, Expected: %d. ", cardCount, 0);
    assertTest(cardCount == 0);

    // Hand
    printf(YELLOW "Test card in hand.\n" RESET);
    
    memset(&game, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &game);

    game.handCount[player] = 5;
    game.hand[player][0] = card;
    memcpy(&testGame, &game, sizeof(struct gameState));

    cardCount = fullDeckCount(player, card, &testGame);
    printf("Card count: %d, Expected: %d. ", cardCount, 1);
    assertTest(cardCount == 1);

    // Deck
    printf(YELLOW "Test card in deck.\n" RESET);

    memset(&game, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &game);

    game.deck[player][0] = card;
    memcpy(&testGame, &game, sizeof(struct gameState));

    cardCount = fullDeckCount(player, card, &testGame);
    printf("Card count: %d, Expected: %d. ", cardCount, 1);
    assertTest(cardCount == 1);

    // Discard
    printf(YELLOW "Test card in discard.\n" RESET);
    memset(&game, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &game);

    game.discardCount[player] = 5;
    game.discard[player][0] = card;
    memcpy(&testGame, &game, sizeof(struct gameState));

    cardCount = fullDeckCount(player, card, &testGame);
    printf("Card count: %d, Expected: %d. ", cardCount, 1);
    assertTest(cardCount == 1);
  }




  return 0;
}

  /*
  int fullDeckCount(int player, int card, struct gameState *state) {
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
}*/