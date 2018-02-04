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
	int seed = 1000;
  int numPlayers = 2;
  int player = 0;
  int player2 = 1;
  int player2HandSize = 5;
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
               village, baron, great_hall};
  int bonus = 0;
  int handPos = 0;
  
  struct gameState game, testGame, preTestGame;

  printf("-- Testing smithy -- \n\n");
  printf(YELLOW "Testing player receives three cards.\n" RESET);

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  cardEffect(smithy, -1, -1, -1, &testGame, handPos, &bonus);

  int i;
  for (i = 0; i < 3; i++) {
  	drawCard(player, &game);
  }

  discardCard(handPos, player, &game, 0);

  printf("Hand count = %d, Expected = %d. ", testGame.handCount[player], game.handCount[player]);
  assertTest(testGame.handCount[player] == game.handCount[player]);
  printf("Deck count = %d, Expected = %d. ", testGame.deckCount[player], game.deckCount[player]);
  assertTest(testGame.handCount[player] == game.handCount[player]);
  printf("\n");

  printf(YELLOW "Testing cards have come from players own pile.\n" RESET);

  int cardsDrawn = testGame.handCount[player] + 1 - preTestGame.handCount[player];
  printf("Deck count = %d, Expected = %d. ", testGame.deckCount[player], preTestGame.deckCount[player] - cardsDrawn);
  assertTest(testGame.deckCount[player] == preTestGame.deckCount[player] - cardsDrawn);
  
  printf("\n");

  printf(YELLOW "Testing player calls discardCard on smithy card after use.\n" RESET);

  printf("Top played card value = %d, Expected = %d. ", 
  			 testGame.playedCards[testGame.playedCardCount - 1], 
  			 game.playedCards[game.playedCardCount - 1]);
  assertTest(testGame.playedCards[testGame.playedCardCount - 1] == game.playedCards[game.playedCardCount - 1]);

  printf("\n");

  printf(YELLOW "Testing no state change has occured for other player\n" RESET);

  printf("Hand for player 2 remains the same: ");
  assertTest(memcmp(game.hand[player2], testGame.hand[player2], sizeof (int) * player2HandSize) == 0);

  printf("Deck for player 2 remains the same: ");
  assertTest(memcmp(game.deck[player2], testGame.deck[player2], sizeof (int) * player2HandSize) == 0);

  printf("Discard pile for player 2 remains the same: ");
  assertTest(memcmp(game.discard[player2], testGame.discard[player2], sizeof (int) * player2HandSize) == 0);

  printf("\n");
  printf(YELLOW "Testing no state change has occured to victory card piles. \n" RESET);
  printf("Estate pile count = %d, Expected = %d. ", testGame.supplyCount[estate], game.supplyCount[estate]);
  assertTest(testGame.supplyCount[estate] == game.supplyCount[estate]);

  printf("Duchy pile count = %d, Expected = %d. ", testGame.supplyCount[duchy], game.supplyCount[duchy]);
  assertTest(testGame.supplyCount[duchy] == game.supplyCount[duchy]);

  printf("Province pile count = %d, Expected = %d. ", testGame.supplyCount[province], game.supplyCount[province]);
  assertTest(testGame.supplyCount[province] == game.supplyCount[province]);

  printf("\n");
  printf(YELLOW "Testing no state change has occured to kingdom card piles. \n" RESET);

  for (i = 0; i < 10; i++) {
  	printf("Number of card number %d = %d, Expected = %d. ", k[i], testGame.supplyCount[k[i]], game.supplyCount[k[i]]);
  	assertTest(testGame.supplyCount[k[i]] == game.supplyCount[k[i]]);
  }

	return 0;
}

/*
int playSmithy(struct gameState *state, int currentPlayer, int handPos) {
  int i;

  // +3 Cards
  for (i = 0; i <= 3; i++) {
    drawCard(currentPlayer, state);
  }
      
  // discard card from hand
  discardCard(handPos, currentPlayer, state, 0);

  return 0;
}
*/
