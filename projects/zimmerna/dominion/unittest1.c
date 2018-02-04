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
	/*
		Test list
		1) Province supply is empty
		2) Any three supply piles are empty
    3) Players turn is over
    4) Test supply count
	*/
  /*
  Province boundary cases
  Pr = 0
  Pr > 1
  Pr = 8, 12

  Player boundary cases
  P = 1, 2, 3
  P = 3
  */
  
  int seed = 1000;
  int numPlayers;
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
               village, baron, great_hall};
  
  struct gameState game, testGame;
  int gameOverVal;

  printf("-- Testing isGameOver() -- \n");
  printf("Province card pile size check.\n\n");

  for (numPlayers = 2; numPlayers < 4; numPlayers++) {
    printf("-- Number of players = %d --\n", numPlayers);

    int i;
    for (i = 0; i < 3; i++) {
      memset(&game, 23, sizeof(struct gameState));
      initializeGame(numPlayers, k, seed, &game);

      if (i < 2) {
        game.supplyCount[province] = i;
      }
      
      memcpy(&testGame, &game, sizeof(struct gameState));

      if (game.supplyCount[province] == 0) {
        gameOverVal = 1;
      } else {
        gameOverVal = 0;
      }

      printf(YELLOW "Testing province pile size: %d\n" RESET, game.supplyCount[province]);

      // Test game over value
      int testGameOverVal = isGameOver(&testGame);
      printf("Game over code: %d, Expected: %d. ", gameOverVal, testGameOverVal);
      assertTest(testGameOverVal == gameOverVal);

      // Test game state is not changed
      printf("Test other areas of game state remain the same: ");
      assertTest(memcmp(&game, &testGame, sizeof(struct gameState)) == 0);
    }

    int testGameOverVal;
    int gameOverVal = 0;

    memset(&game, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &game);

    for (i = 0; i < 3; i++) {
      if (i > 1) {
        gameOverVal = 1;
      }

      game.supplyCount[i] = 0;
      memcpy(&testGame, &game, sizeof(struct gameState));
      testGameOverVal = isGameOver(&testGame);
      printf(YELLOW "Test %d supply pile empty.\n" RESET, i + 1);
      printf("Game over code: %d, Expected: %d.  ", testGameOverVal, gameOverVal);
      assertTest(testGameOverVal == gameOverVal);
      printf("Test other areas of game state remain the same: ");
      assertTest(memcmp(&game, &testGame, sizeof(struct gameState)) == 0);
    }

    printf("\n");
  }

  return 0;
}

/*int isGameOver(struct gameState *state) {
  int i;
  int j;
	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }
  if ( j >= 3)
    {
      return 1;
    }

  return 0;
}
*/