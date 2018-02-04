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
  int numPlayers;
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
               village, baron, great_hall};
  
  struct gameState game, testGame;
  int currentPlayer = 0;
  int handPos = 0;
  int trashFlag;
  int handCount;

  // Check that trashed card is not added to Played pile
  printf("-- Testing discardCard() -- \n\n");

  int i;
  for (numPlayers = 2; numPlayers < 4; numPlayers++) {
  	printf("-- Number of players = %d --\n", numPlayers);
  	for (i = 0; i < 2; i++) {
  		handPos = 0;
  		currentPlayer = 0;

  		memset(&game, 23, sizeof(struct gameState));
  		initializeGame(numPlayers, k, seed, &game);
  		game.handCount[currentPlayer] = 1;

  		memcpy(&testGame, &game, sizeof(struct gameState));
  		printf(YELLOW "Test trash flag = %d\n" RESET, i);

      if (i < 1) {
      	game.playedCards[game.playedCardCount] = game.hand[currentPlayer][handPos];
      	game.playedCardCount++;
      }

      game.hand[currentPlayer][handPos] = -1;
      game.handCount[currentPlayer]--;

  		discardCard(handPos, currentPlayer, &testGame, i);
  		printf("Played card count = %d, Expected: %d. ", testGame.playedCardCount, game.playedCardCount);
  		assertTest(testGame.playedCardCount == game.playedCardCount);

  		if (i < 1) {
  			printf("Card added to played pile = %d, Expected: %d. ", testGame.playedCards[testGame.playedCardCount - 1], game.playedCards[game.playedCardCount - 1]);
  			assertTest(testGame.playedCards[testGame.playedCardCount - 1] == game.playedCards[game.playedCardCount - 1]);
  		}

  		printf("Test other areas of game state remain the same: ");
  		assertTest(memcmp(&game, &testGame, sizeof(struct gameState)) == 0);
  	}
  	printf("\n");

  	printf(YELLOW "-- Test hand position --\n" RESET);
  	int flag = 0;
  	handPos = 4;

  	// Min hand pos
  	printf("Test 1 card in hand. \n");
  	memset(&game, 23, sizeof(struct gameState));
  	initializeGame(numPlayers, k, seed, &game);
  	game.handCount[currentPlayer] = 1;
  	memcpy(&testGame, &game, sizeof(struct gameState));

  	discardCard(handPos, currentPlayer, &testGame, flag);

  	game.playedCards[game.playedCardCount] = game.hand[currentPlayer][handPos];
    game.playedCardCount++;

  	game.hand[currentPlayer][handPos] = -1;
    game.handCount[currentPlayer]--;

    printf("Hand count = %d, Expected: %d. ", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
  	assertTest(testGame.handCount[currentPlayer] == game.handCount[currentPlayer]);

  	printf("Card added to played pile = %d, Expected: %d. ", testGame.playedCards[testGame.playedCardCount - 1], game.playedCards[game.playedCardCount - 1]);
  	assertTest(testGame.playedCards[testGame.playedCardCount - 1] == game.playedCards[game.playedCardCount - 1]);

  	printf("New hand position value = %d, Expected: %d. ", testGame.hand[currentPlayer][handPos], game.hand[currentPlayer][handPos]);
  	assertTest(testGame.hand[currentPlayer][handPos] == game.hand[currentPlayer][handPos]);
  	
  	printf("Test other areas of game state remain the same: ");
  	assertTest(memcmp(&game, &testGame, sizeof(struct gameState)) == 0);

  	printf("\n");

  	// Min hand pos + 1
  	handPos = 0;

  	printf("Test position 0 played with 2 cards in hand.\n");
  	memset(&game, 23, sizeof(struct gameState));
  	initializeGame(numPlayers, k, seed, &game);
  	game.handCount[currentPlayer] = 2;
  	memcpy(&testGame, &game, sizeof(struct gameState));

  	discardCard(handPos, currentPlayer, &testGame, flag);

  	game.playedCards[game.playedCardCount] = game.hand[currentPlayer][handPos];
    game.playedCardCount++;

  	game.hand[currentPlayer][handPos] = -1;
    //replace discarded card with last card in hand
    game.hand[currentPlayer][handPos] = game.hand[currentPlayer][ (game.handCount[currentPlayer] - 1)];
    //set last card to -1
    game.hand[currentPlayer][game.handCount[currentPlayer] - 1] = -1;
    //reduce number of cards in hand
    game.handCount[currentPlayer]--;

    printf("Hand count = %d, Expected: %d. ", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
  	assertTest(testGame.handCount[currentPlayer] == game.handCount[currentPlayer]);

  	printf("Card added to played pile = %d, Expected: %d. ", testGame.playedCards[testGame.playedCardCount - 1], game.playedCards[game.playedCardCount - 1]);
  	assertTest(testGame.playedCards[testGame.playedCardCount - 1] == game.playedCards[game.playedCardCount - 1]);

  	printf("New hand position value = %d, Expected: %d. ", testGame.hand[currentPlayer][handPos], game.hand[currentPlayer][handPos]);
  	assertTest(testGame.hand[currentPlayer][handPos] == game.hand[currentPlayer][handPos]);
  	
  	printf("Test other areas of game state remain the same: ");
  	assertTest(memcmp(&game, &testGame, sizeof(struct gameState)) == 0);

  	printf("\n");
  	
  	// Max hand pos
  	handPos = 499;

  	printf("Test position 499 played with 500 cards in hand. \n");
  	memset(&game, 23, sizeof(struct gameState));
  	initializeGame(numPlayers, k, seed, &game);
  	game.handCount[currentPlayer] = MAX_HAND;
  	game.hand[currentPlayer][handPos] = 499;
  	memcpy(&testGame, &game, sizeof(struct gameState));

  	discardCard(handPos, currentPlayer, &testGame, flag);

  	game.playedCards[game.playedCardCount] = game.hand[currentPlayer][handPos];
    game.playedCardCount++;

  	game.hand[currentPlayer][handPos] = -1;
    game.handCount[currentPlayer]--;

    printf("Hand count = %d, Expected: %d. ", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
  	assertTest(testGame.handCount[currentPlayer] == game.handCount[currentPlayer]);

  	printf("Card added to played pile = %d, Expected: %d. ", testGame.playedCards[testGame.playedCardCount - 1], game.playedCards[game.playedCardCount - 1]);
  	assertTest(testGame.playedCards[testGame.playedCardCount - 1] == game.playedCards[game.playedCardCount - 1]);

  	printf("New hand position value = %d, Expected: %d. ", testGame.hand[currentPlayer][handPos], game.hand[currentPlayer][handPos]);
  	assertTest(testGame.hand[currentPlayer][handPos] == game.hand[currentPlayer][handPos]);
  	
  	printf("Test other areas of game state remain the same: ");
  	assertTest(memcmp(&game, &testGame, sizeof(struct gameState)) == 0);

  	printf("\n");

  	printf(YELLOW "-- Test played card added to the discard pile. --\n" RESET);

  	game.discard[currentPlayer][game.discardCount[currentPlayer]] = handPos;
  	game.discardCount[currentPlayer]++;

  	printf("Card on top of discard pile = %d, Expected = %d. ", testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1], 
  				 game.discard[currentPlayer][game.discardCount[currentPlayer] - 1]);
  	assertTest(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] == game.discard[currentPlayer][game.discardCount[currentPlayer] - 1]);

  	printf("\n");
  }

	return 0;
}

/*
int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{
	
  //if card is not trashed, added to Played pile 
  if (trashFlag < 1)
    {
      //add card to played pile
      state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos]; 
      state->playedCardCount++;
    }
	
  //set played card to -1
  state->hand[currentPlayer][handPos] = -1;
	
  //remove card from[currentPlayer's hand
  if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
    {
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
    }
  else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
    {
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
    }
  else 	
    {
      //replace discarded card with last card in hand
      state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
      //set last card to -1
      state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
    }
	
  return 0;
}
*/