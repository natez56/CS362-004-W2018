/*********************************************************************
** Program name: unittest1
** Author: Nathan Zimmerman
** Date: 02/04/2018
** Description: Unit test for isGameOver() function.
how to run it: make unittestresults.out or make unittest1 and then
./unittest1
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
  int seed = 1000;
  int numPlayers;
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
               village, baron, great_hall}; 
  struct gameState game, testGame;
  int gameOverVal;

  printf("-- Testing isGameOver() -- \n");
  printf("Province card pile size check.\n\n");

  // Test for instances where players > 2 and total pile counts are increased.
  for (numPlayers = 2; numPlayers < 4; numPlayers++) {
    printf("-- Number of players = %d --\n", numPlayers);

    int i;
    for (i = 0; i < 3; i++) {
      // Clear game state and initialize new game.
      memset(&game, 23, sizeof(struct gameState));
      initializeGame(numPlayers, k, seed, &game);

      // Manually simulate correct behavior.
      if (i < 2) {
        game.supplyCount[province] = i;
      }
      
      memcpy(&testGame, &game, sizeof(struct gameState));

      if (game.supplyCount[province] == 0) {
        gameOverVal = 1;
      } else {
        gameOverVal = 0;
      }

      printf("\n");

      printf(YELLOW "Testing province pile size: %d\n" RESET, game.supplyCount[province]);

      // Test game over value for varying province piles sizes by comparing
      // simulated return values with game state of function call.
      int testGameOverVal = isGameOver(&testGame);
      printf("Game over code: %d, Expected: %d. ", gameOverVal, testGameOverVal);
      assertTest(testGameOverVal == gameOverVal);

      // Test that game state is not changed due to function call.
      printf("Test other areas of game state remain the same: ");
      assertTest(memcmp(&game, &testGame, sizeof(struct gameState)) == 0);
    }

    int testGameOverVal;
    int gameOverVal = 0;

    // Clear and re-initialize game state.
    memset(&game, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &game);

    // Test supply count trigger by simulating 1, 2, and then 3 empty supplies.
    for (i = 0; i < 3; i++) {
      if (i > 1) {
        gameOverVal = 1;
      }

      game.supplyCount[i] = 0;

      memcpy(&testGame, &game, sizeof(struct gameState));
   
      testGameOverVal = isGameOver(&testGame);

      printf("\n");

      printf(YELLOW "Test %d supply pile empty.\n" RESET, i + 1);

      // Compare game state after function call with what should be the correct
      // return value.
      printf("Game over code: %d, Expected: %d.  ", testGameOverVal, gameOverVal);
      assertTest(testGameOverVal == gameOverVal);

      // Test to ensure function call does not alter other areas of game state.
      printf("Test other areas of game state remain the same: ");
      assertTest(memcmp(&game, &testGame, sizeof(struct gameState)) == 0);
    }
    printf("\n");

  }

  return 0;
}