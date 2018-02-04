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

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.supplyCount[1] = 0; 
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  returnVal = gainCard(1, &testGame, 1, player);

  printf("Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  printf("\n");
  printf(YELLOW "Testing gained card goes to deck.\n" RESET);

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);
 
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  gainCard(1, &testGame, 1, player);

  game.deckCount[player]++;
  game.deck[player][game.deckCount[player] - 1] = 1;

  printf("Card added to deck = %d, Expected = %d. ", testGame.deck[player][testGame.deckCount[player] - 1], 
  			 game.deck[player][game.deckCount[player] - 1]);
  assertTest(testGame.deck[player][testGame.deckCount[player] - 1] == game.deck[player][game.deckCount[player] - 1]);

  printf("\n");
  printf(YELLOW "Testing gained card goes to hand.\n" RESET);

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);
 
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  gainCard(1, &testGame, 2, player);

  game.handCount[player]++;
  game.hand[player][game.handCount[player] - 1] = 1;

  printf("Card added to hand = %d, Expected = %d. ", testGame.hand[player][testGame.handCount[player] - 1], 
  			 game.hand[player][game.handCount[player] - 1]);
  assertTest(testGame.hand[player][testGame.handCount[player] - 1] == game.hand[player][game.handCount[player] - 1]);

  printf("\n");
  printf(YELLOW "Testing gained card goes to discard.\n" RESET);

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);
 
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  gainCard(1, &testGame, 3, player);

  game.discardCount[player]++;
  game.discard[player][game.discardCount[player] - 1] = 1;
  game.supplyCount[1]--;

  printf("Card added to hand = %d, Expected = %d. ", testGame.discard[player][testGame.discardCount[player] - 1], 
  			 game.discard[player][game.discardCount[player] - 1]);
  assertTest(testGame.discard[player][testGame.discardCount[player] - 1] == game.discard[player][game.discardCount[player] - 1]);

  printf("\n");
  printf(YELLOW "Testing supply count updated.\n" RESET);

  printf("Supply count = %d, Expected = %d. ", testGame.supplyCount[1], game.supplyCount[1]);
  assertTest(testGame.discard[player][testGame.discardCount[player] - 1] == game.discard[player][game.discardCount[player] - 1]);

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
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
{
  //Note: supplyPos is enum of choosen card
	
  //check if supply pile is empty (0) or card is not used in game (-1)
  if ( supplyCount(supplyPos, state) < 1 )
    {
      return -1;
    }
	
  //added card for [whoseTurn] current player:
  // toFlag = 0 : add to discard
  // toFlag = 1 : add to deck
  // toFlag = 2 : add to hand

  if (toFlag == 1)
    {
      state->deck[ player ][ state->deckCount[player] ] = supplyPos;
      state->deckCount[player]++;
    }
  else if (toFlag == 2)
    {
      state->hand[ player ][ state->handCount[player] ] = supplyPos;
      state->handCount[player]++;
    }
  else
    {
      state->discard[player][ state->discardCount[player] ] = supplyPos;
      state->discardCount[player]++;
    }
	
  //decrease number in supply pile
  state->supplyCount[supplyPos]--;
	 
  return 0;
}
*/