/********************************************************************
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
  int i;
	int seed = 1000;
  int numPlayers = 2;
  int player = 0;
  int player2 = 1;
  int player2HandSize = 5;
  
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
               village, baron, great_hall};
  int bonus = 0;
  int handPos = 0;
  int cardsDrawn = 0;
  
  
  struct gameState game, testGame, preTestGame;

  printf("-- Testing village -- \n\n");

  printf(YELLOW "Testing player draws 1 card.\n" RESET);
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  cardEffect(village, -1, -1, -1, &testGame, handPos, &bonus);

  drawCard(player, &game);
  game.numActions = game.numActions + 2;
  discardCard(handPos, player, &game, 0);

  printf("Hand count = %d, Expected = %d. ", testGame.handCount[player], game.handCount[player]);
  assertTest(testGame.handCount[player] == preTestGame.handCount[player]);
  printf("Deck count = %d, Expected = %d. ", testGame.deckCount[player], game.deckCount[player]);
  assertTest(testGame.deckCount[player] == game.deckCount[player]);

  printf("\n");

  printf(YELLOW "Testing drawn cards come from player's own pile.\n" RESET);
  cardsDrawn = preTestGame.deckCount[player] - testGame.deckCount[player];
  printf("Deck count = %d, Expected = %d. ", testGame.deckCount[player], preTestGame.deckCount[player] - cardsDrawn);
  assertTest(testGame.deckCount[player] == preTestGame.deckCount[player] - cardsDrawn);

  printf("\n");

  printf(YELLOW "Testing player receives +2 actions.\n" RESET);

  printf("Number of actions = %d, Expected = %d. ", testGame.numActions, game.numActions);
  assertTest(testGame.numActions == game.numActions);
  printf("\n");
  printf("\n");

  printf(YELLOW "Testing player calls discardCard on village card after use.\n" RESET);

  printf("Top played card value = %d, Expected = %d. ", 
         testGame.playedCards[testGame.playedCardCount - 1], 
         game.playedCards[game.playedCardCount - 1]);
  assertTest(testGame.playedCards[testGame.playedCardCount - 1] == game.playedCards[game.playedCardCount - 1]);

  printf("\n");

  printf(YELLOW "Testing no state change for other players.\n" RESET);

  printf("Hand for player 2 remains the same: ");
  assertTest(memcmp(game.hand[player2], testGame.hand[player2], sizeof (int) * player2HandSize) == 0);

  printf("Deck for player 2 remains the same: ");
  assertTest(memcmp(game.deck[player2], testGame.deck[player2], sizeof (int) * player2HandSize) == 0);

  printf("Discard pile for player 2 remains the same: ");
  assertTest(memcmp(game.discard[player2], testGame.discard[player2], sizeof (int) * player2HandSize) == 0);

  printf("\n");

  printf(YELLOW "Testing no state change to the victory card pile.\n" RESET);

  printf("Estate pile count = %d, Expected = %d. ", testGame.supplyCount[estate], game.supplyCount[estate]);
  assertTest(testGame.supplyCount[estate] == game.supplyCount[estate]);

  printf("Duchy pile count = %d, Expected = %d. ", testGame.supplyCount[duchy], game.supplyCount[duchy]);
  assertTest(testGame.supplyCount[duchy] == game.supplyCount[duchy]);

  printf("Province pile count = %d, Expected = %d. ", testGame.supplyCount[province], game.supplyCount[province]);
  assertTest(testGame.supplyCount[province] == game.supplyCount[province]);

  printf("\n");

  printf(YELLOW "Testing no state change to the kingdom card pile.\n" RESET);

  for (i = 0; i < 10; i++) {
    printf("Number of card number %d = %d, Expected = %d. ", k[i], testGame.supplyCount[k[i]], game.supplyCount[k[i]]);
    assertTest(testGame.supplyCount[k[i]] == game.supplyCount[k[i]]);
  }

  return 0;

}

/*
int playVillage(struct gameState *state, int player, int handPos) {
  // +1 Card
  drawCard(player, state);
      
  // +2 Actions
  state->numActions = state->numActions + 2;
      
  // discard played card from hand
  // discardCard(handPos, player, state, 0);

  return 0;
}
*/