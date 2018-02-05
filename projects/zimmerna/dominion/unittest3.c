/*********************************************************************
** Program name: unittest3
** Author: Nathan Zimmerman
** Date: 02/04/2018
** Description: Unit test for fullDeckCount() function.
how to run it: make unittestresults.out or make unittest3 and then
./unittest3
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
  int player;
  int player2 = 1;
  int player2HandSize = 5;
  int card = -1;
  int cardCount;
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
               village, baron, great_hall};
  struct gameState game, testGame;

  printf("-- Testing fullDeckCount() -- \n\n");

  // For loop to test function for different players.
  for (player = 0; player < numPlayers; player++) {
    printf("-- Player = %d --\n", player);

    printf(YELLOW "Test card not in deck.\n" RESET);

    // Clear game state and initialize new game state.
    memset(&game, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &game);

    // Set testGame state to game state.
    memcpy(&testGame, &game, sizeof(struct gameState));

    cardCount = fullDeckCount(player, card, &testGame);

    // Card not in deck, should not be found.
    printf("Deck count: %d, Expected: %d. ", cardCount, 0);
    assertTest(cardCount == 0);

    printf("\n");

    printf(YELLOW "Test card in hand.\n" RESET);
    
    // Clear game state and re-initialize so that function can be called again.
    memset(&game, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &game);

    // Valid card added to hand.
    game.handCount[player] = 5;
    game.hand[player][0] = card;

    memcpy(&testGame, &game, sizeof(struct gameState));

    cardCount = fullDeckCount(player, card, &testGame);

    // Card value is unique. Only one should be found.
    printf("Card count: %d, Expected: %d. ", cardCount, 1);
    assertTest(cardCount == 1);

    printf("\n");

    printf(YELLOW "Test card in deck.\n" RESET);

    // Clear game state and re-initialize so that function can be called again.
    memset(&game, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &game);

    game.deck[player][0] = card;

    memcpy(&testGame, &game, sizeof(struct gameState));

    cardCount = fullDeckCount(player, card, &testGame);

    // Card value is unique. Only one should be found.
    printf("Card count: %d, Expected: %d. ", cardCount, 1);
    assertTest(cardCount == 1);

    printf("\n");

    printf(YELLOW "Test card in discard.\n" RESET);

    // Clear game state and re-initialize so that function can be called again.
    memset(&game, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &game);

    game.discardCount[player] = 5;
    game.discard[player][0] = card;

    memcpy(&testGame, &game, sizeof(struct gameState));

    cardCount = fullDeckCount(player, card, &testGame);

    // Card value is unique, only one should be found.
    printf("Card count: %d, Expected: %d. ", cardCount, 1);
    assertTest(cardCount == 1);

    // Set other player value so that test can be run to ensure function call
    // does not change their states.
    if (player == 0) {
      player2 = 1;
    } else if (player == 1) {
      player2 = 0;
    } else {
      player2 = 1;
    }

    printf("\n");

    printf(YELLOW "Testing no state change has occured for other player\n" RESET);

    // Player2 state should not change since function is called for player1 value.
    printf("Hand for player %d remains the same: ", player2);
    assertTest(memcmp(game.hand[player2], testGame.hand[player2], sizeof (int) * player2HandSize) == 0);

    printf("Deck for player %d remains the same: ", player2);
    assertTest(memcmp(game.deck[player2], testGame.deck[player2], sizeof (int) * player2HandSize) == 0);

    printf("Discard pile for player %d remains the same: ", player2);
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
  }

  return 0;
}