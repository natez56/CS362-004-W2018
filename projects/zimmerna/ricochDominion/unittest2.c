/*********************************************************************
** Program name: unittest2
** Author: Nathan Zimmerman
** Date: 02/04/2018
** Description: Unit test for discardCard() function.
how to run it: make unittestresults.out or make unittest2 and then
./unittest2
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
  int numPlayers;
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
               village, baron, great_hall};
  
  struct gameState game, testGame;
  int currentPlayer = 0;
  int player2 = 1;
  int player2HandSize = 5;
  int handPos = 0;
  int trashFlag;

  printf("-- Testing discardCard() -- \n\n");

  // Test function effect when pile sizes chande do to different number of players. 
  for (numPlayers = 2; numPlayers < 4; numPlayers++) {
  	printf("-- Number of players = %d --\n", numPlayers);

    // Loop to test trash flag 0 and 1.
  	for (trashFlag = 0; trashFlag < 2; trashFlag++) {
  		handPos = 0;
  		currentPlayer = 0;

      // Clear game state and initialize new game.
  		memset(&game, 23, sizeof(struct gameState));
  		initializeGame(numPlayers, k, seed, &game);

      // Set hand count to 1 to track card easier.
  		game.handCount[currentPlayer] = 1;

      // Set game states so that they all have the same handCount.
  		memcpy(&testGame, &game, sizeof(struct gameState));

  		printf(YELLOW "Test trash flag = %d\n" RESET, i);

      // Simulate correct behavior by moving card to played pile.
      if (trashFlag < 1) {
      	game.playedCards[game.playedCardCount] = game.hand[currentPlayer][handPos];
      	game.playedCardCount++;
      }

      // Simulate removing card from hand.
      game.hand[currentPlayer][handPos] = -1;
      game.handCount[currentPlayer]--;

  		discardCard(handPos, currentPlayer, &testGame, trashFlag);

      // Compare simulated behavior game state to function call game state.
  		printf("Played card count = %d, Expected: %d. ", testGame.playedCardCount, game.playedCardCount);
  		assertTest(testGame.playedCardCount == game.playedCardCount);

      // Test that the card added to play pile matches for both game states.
  		if (trashFlag < 1) {
  			printf("Card added to played pile = %d, Expected: %d. ", testGame.playedCards[testGame.playedCardCount - 1], game.playedCards[game.playedCardCount - 1]);
  			assertTest(testGame.playedCards[testGame.playedCardCount - 1] == game.playedCards[game.playedCardCount - 1]);
  		}

      // Make sure function call doesn't affect other areas of the game.
  		printf("Test other areas of game state remain the same: ");
  		assertTest(memcmp(&game, &testGame, sizeof(struct gameState)) == 0);
  	}

  	printf("\n");

  	printf(YELLOW "-- Test hand position --\n" RESET);
  	trashFlag = 0;
  	handPos = 4;

  	// Test case where handPos is not 0 even though card is last card. handPos = 4
    // Triggers conditional statement found in discardCard() function.
  	printf("Test 1 card in hand. \n");

    // Clear game state and re-initialize so function can be called again.
  	memset(&game, 23, sizeof(struct gameState));
  	initializeGame(numPlayers, k, seed, &game);

  	game.handCount[currentPlayer] = 1;

  	memcpy(&testGame, &game, sizeof(struct gameState));

  	discardCard(handPos, currentPlayer, &testGame, trashFlag);

    // Simulate correct behavior. Hand emptied.
  	game.playedCards[game.playedCardCount] = game.hand[currentPlayer][handPos];
    game.playedCardCount++;

  	game.hand[currentPlayer][handPos] = -1;
    game.handCount[currentPlayer]--;

    // Compare simulated behavior to function call game state.
    printf("Hand count = %d, Expected: %d. ", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
  	assertTest(testGame.handCount[currentPlayer] == game.handCount[currentPlayer]);

  	printf("Card added to played pile = %d, Expected: %d. ", testGame.playedCards[testGame.playedCardCount - 1], game.playedCards[game.playedCardCount - 1]);
  	assertTest(testGame.playedCards[testGame.playedCardCount - 1] == game.playedCards[game.playedCardCount - 1]);

  	printf("New hand position value = %d, Expected: %d. ", testGame.hand[currentPlayer][handPos], game.hand[currentPlayer][handPos]);
  	assertTest(testGame.hand[currentPlayer][handPos] == game.hand[currentPlayer][handPos]);
  	
  	printf("Test other areas of game state remain the same: ");
  	assertTest(memcmp(&game, &testGame, sizeof(struct gameState)) == 0);

  	printf("\n");

  	// Min hand pos + 1. Testing different conditional statement in discardCard().
  	handPos = 0;

  	printf("Test position 0 played with 2 cards in hand.\n");

    // Clear and re-initialize game state so that function can be called again.
  	memset(&game, 23, sizeof(struct gameState));
  	initializeGame(numPlayers, k, seed, &game);

  	game.handCount[currentPlayer] = 2;
  	memcpy(&testGame, &game, sizeof(struct gameState));

  	discardCard(handPos, currentPlayer, &testGame, trashFlag);

    // Simulate behavior of removing card in position 0. 
  	game.playedCards[game.playedCardCount] = game.hand[currentPlayer][handPos];
    game.playedCardCount++;

  	game.hand[currentPlayer][handPos] = -1;

    // Replace discarded card with last card in hand.
    game.hand[currentPlayer][handPos] = game.hand[currentPlayer][ (game.handCount[currentPlayer] - 1)];

    // Set last card to -1.
    game.hand[currentPlayer][game.handCount[currentPlayer] - 1] = -1;

    // Reduce number of cards in hand.
    game.handCount[currentPlayer]--;

    // Compare simulated correct behavior to game state that called function.
    printf("Hand count = %d, Expected: %d. ", testGame.handCount[currentPlayer], game.handCount[currentPlayer]);
  	assertTest(testGame.handCount[currentPlayer] == game.handCount[currentPlayer]);

  	printf("Card added to played pile = %d, Expected: %d. ", testGame.playedCards[testGame.playedCardCount - 1], game.playedCards[game.playedCardCount - 1]);
  	assertTest(testGame.playedCards[testGame.playedCardCount - 1] == game.playedCards[game.playedCardCount - 1]);

  	printf("New hand position value = %d, Expected: %d. ", testGame.hand[currentPlayer][handPos], game.hand[currentPlayer][handPos]);
  	assertTest(testGame.hand[currentPlayer][handPos] == game.hand[currentPlayer][handPos]);
  	
  	printf("Test other areas of game state remain the same: ");
  	assertTest(memcmp(&game, &testGame, sizeof(struct gameState)) == 0);

  	printf("\n");
  	
  	// Testing last card is discarded. Max hand size used.
  	handPos = 499;

    // Test large hand size to ensure that it works.
  	printf("Test position 499 played with 500 cards in hand. \n");

    // Clear game state and re-initialize so that function can be called again.
  	memset(&game, 23, sizeof(struct gameState));
  	initializeGame(numPlayers, k, seed, &game);

  	game.handCount[currentPlayer] = MAX_HAND;
  	game.hand[currentPlayer][handPos] = 499;

    // Ensure that testGame is using same hand as game.
  	memcpy(&testGame, &game, sizeof(struct gameState));

  	discardCard(handPos, currentPlayer, &testGame, trashFlag);

    // Simulate removing the last card in hand.
  	game.playedCards[game.playedCardCount] = game.hand[currentPlayer][handPos];
    game.playedCardCount++;

  	game.hand[currentPlayer][handPos] = -1;
    game.handCount[currentPlayer]--;

    // Compare simulated correct behavior to game state of testGame where function is called.
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

    // Using same game state as prior test. Function already called.
    // Because card is removed from hand it should be added to the discard pile.
  	game.discard[currentPlayer][game.discardCount[currentPlayer]] = handPos;
  	game.discardCount[currentPlayer]++;

    // Compare game states to ensure function behavior is same as simulated correct behavior.
  	printf("Card on top of discard pile = %d, Expected = %d. ", testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1], 
  				 game.discard[currentPlayer][game.discardCount[currentPlayer] - 1]);
  	assertTest(testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] == game.discard[currentPlayer][game.discardCount[currentPlayer] - 1]);

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
  }

	return 0;
}