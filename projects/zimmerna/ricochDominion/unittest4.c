/*********************************************************************
** Program name: unittest4
** Author: Nathan Zimmerman
** Date: 02/04/2018
** Description: Unit test for gainCard() function.
how to run it: make unittestresults.out or make unittest4 and then
./unittest4
*********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define COLORED_OUTPUT 0

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1B[33m"
#define RESET   "\x1b[0m"

#if COLORED_OUTPUT == 0
#undef RED
#undef GREEN
#undef YELLOW
#undef RESET
#define RED     ""
#define GREEN   ""
#define YELLOW  ""
#define RESET   ""
#endif

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
  int returnVal;
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
               village, baron, great_hall}; 
  struct gameState game, testGame, preTestGame;

  printf("-- Testing gainCard() -- \n\n");

  printf(YELLOW "Testing supply for card is empty.\n" RESET);

  // Clear game state and initialize new game.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  // Set supply count to test.
  game.supplyCount[1] = 0;

  // Copy state with correct supply count to test states.
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  returnVal = gainCard(1, &testGame, 1, player);

  // Supply is empty, card cannot be gained.
  printf("Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  printf("\n");

  printf(YELLOW "Testing gained card goes to deck.\n" RESET);

  // Clear game state and re-initialize so that function can be called again.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);
 
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  gainCard(1, &testGame, 1, player);

  // Simulate gaining card to deck.
  game.deckCount[player]++;
  game.deck[player][game.deckCount[player] - 1] = 1;

  // Compare correctly simulated state with state of testGame where function is called.
  printf("Card added to deck = %d, Expected = %d. ", testGame.deck[player][testGame.deckCount[player] - 1], 
  			 game.deck[player][game.deckCount[player] - 1]);
  assertTest(testGame.deck[player][testGame.deckCount[player] - 1] == game.deck[player][game.deckCount[player] - 1]);

  printf("\n");

  printf(YELLOW "Testing gained card goes to hand.\n" RESET);

  // Clear game state and re-initialize so that function can be called again.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);
 
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  gainCard(1, &testGame, 2, player);

  // Simulate gaining card to hand.
  game.handCount[player]++;
  game.hand[player][game.handCount[player] - 1] = 1;

  // Compare correctly simulated state with state of testGame where function is called.
  printf("Card added to hand = %d, Expected = %d. ", testGame.hand[player][testGame.handCount[player] - 1], 
  			 game.hand[player][game.handCount[player] - 1]);
  assertTest(testGame.hand[player][testGame.handCount[player] - 1] == game.hand[player][game.handCount[player] - 1]);

  printf("\n");

  printf(YELLOW "Testing gained card goes to discard.\n" RESET);

  // Clear game state and re-initialize so that function can be called again.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);
 
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  gainCard(1, &testGame, 3, player);

  // Simulate gaining card to discard pile.
  game.discardCount[player]++;
  game.discard[player][game.discardCount[player] - 1] = 1;

  // Used for supply count test.
  game.supplyCount[1]--;

  // Compare correctly simulated state with state of testGame where function is called.
  printf("Card added to discard pile = %d, Expected = %d. ", testGame.discard[player][testGame.discardCount[player] - 1], 
  			 game.discard[player][game.discardCount[player] - 1]);
  assertTest(testGame.discard[player][testGame.discardCount[player] - 1] == game.discard[player][game.discardCount[player] - 1]);

  printf("\n");

  printf(YELLOW "Testing supply count updated.\n" RESET);

  // Compare correctly simulated state with state of testGame where function is called.
  printf("Supply count = %d, Expected = %d. ", testGame.supplyCount[1], game.supplyCount[1]);
  assertTest(testGame.discard[player][testGame.discardCount[player] - 1] == game.discard[player][game.discardCount[player] - 1]);

  printf("\n");

  printf(YELLOW "Testing no state change has occured for other player\n" RESET);

  // Player2 state should not change since function is called for player1.
  printf("Hand for player 2 remains the same: ");
  assertTest(memcmp(game.hand[player2], testGame.hand[player2], sizeof (int) * player2HandSize) == 0);

  printf("Deck for player 2 remains the same: ");
  assertTest(memcmp(game.deck[player2], testGame.deck[player2], sizeof (int) * player2HandSize) == 0);

  printf("Discard pile for player 2 remains the same: ");
  assertTest(memcmp(game.discard[player2], testGame.discard[player2], sizeof (int) * player2HandSize) == 0);

  printf("\n");

  printf(YELLOW "Testing no state change has occured to victory card piles. \n" RESET);

  // Comparing game states for testGame where function is called and game, where
  // behavior is manually simulated.
  printf("Estate pile count = %d, Expected = %d. ", testGame.supplyCount[estate], game.supplyCount[estate]);
  assertTest(testGame.supplyCount[estate] == game.supplyCount[estate]);

  printf("Duchy pile count = %d, Expected = %d. ", testGame.supplyCount[duchy], game.supplyCount[duchy]);
  assertTest(testGame.supplyCount[duchy] == game.supplyCount[duchy]);

  printf("Province pile count = %d, Expected = %d. ", testGame.supplyCount[province], game.supplyCount[province]);
  assertTest(testGame.supplyCount[province] == game.supplyCount[province]);

  printf("\n");

  printf(YELLOW "Testing no state change has occured to kingdom card piles. \n" RESET);

  // Loop counts supply of each kingdom card and compares it to state where playSmithy()
  // is not called.
  for (i = 0; i < 10; i++) {
  	printf("Number of card number %d = %d, Expected = %d. ", k[i], testGame.supplyCount[k[i]], game.supplyCount[k[i]]);
  	assertTest(testGame.supplyCount[k[i]] == game.supplyCount[k[i]]);
  }

  printf("\n");

  return 0;
}