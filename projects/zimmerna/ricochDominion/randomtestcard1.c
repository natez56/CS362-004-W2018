/********************************************************************
** Program name: randomtestcard2.c
** Author: Nathan Zimmerman
** Date: 02/18/2018
** Description: Smithy random test generator. Use make randomtestcard1.out
to generate .out file. Or use make randomtestcard1 and then ./randomtestcard1
to run without generating the .out file.
*********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

struct ErrorList {
	// Errors, deck shuffled.
	int numShuffledDeckErrorsHigh;
	int numShuffledDeckErrorsLow;
	int numShuffledHandCountErrorsHigh;
	int numShuffledHandCountErrorsLow;
	int numShuffledDiscardErrorsHigh;
	int numShuffledDiscardErrorsLow;
	int numShuffledOtherPlayerStateErrors;
	int numShuffledVictoryPileErrors;
	int numShuffledSupplyPileErrors;
	int numShuffledSmithyDiscardErrors;

	// No Shuffle Errors.
	int numDeckErrorsHigh;
	int numDeckErrorsLow;
	int numHandCountErrorsHigh;
	int numHandCountErrorsLow;
	int numDiscardErrorsHigh;
	int numDiscardErrorsLow;
	int numOtherPlayerStateErrors;
	int numVictoryPileErrors;
	int numSupplyPileErrors;
	int numSmithyDiscardErrors;
};

int checkSmithy(struct gameState *post, int player, int handPos, int seed, 
                struct ErrorList* errors) {
	int i;

	// Store cardEffect return.
	int result;

	int shuffled = 0;
	int bonus = 0;
	int player2;

	struct gameState pre, initialPre;

	if (player > 0) {
		player2 = 0;
	} else {
		player2 = 1;
	}

	// Reset random seed in case shuffle takes place. This ensures that both the
	// cardEffect drawCard and the drawCard called on pre will have the same shuffle.
	SelectStream(2);
	PutSeed(seed);

	// Copy memory to player 2 for later player 2 state check.
	memcpy(post->hand[player2], post->hand[player], sizeof(int) * post->handCount[player]);
	memcpy(post->deck[player2], post->deck[player], sizeof(int) * post->deckCount[player]);
	memcpy(post->discard[player2], post->discard[player], sizeof(int) * post->discardCount[player]);

	// initialPre used to check initial game state.
	memcpy(&initialPre, post, sizeof(struct gameState));

	// pre state will simulate correct results for game state.
	memcpy(&pre, post, sizeof(struct gameState));
	
	result = cardEffect(smithy, -1, -1, -1, post, handPos, &bonus);

	// Correct behaviour simulated for smithy.
	// Check if shuffle will take place.
	if (pre.deckCount[player] < 3) {
		// Reset random seed if shuffle will take place so that the shuffle will
		// be the same as the cardEffect one.
		SelectStream(2);
		PutSeed(seed);

		// Set shuffle flag to record shuffle errors in separate section of errors.
		shuffled = 1;
	}

  for (i = 0; i < 3; i++) {
    drawCard(player, &pre);
  }
      
  // Discard smithy.
  discardCard(handPos, player, &pre, 0);

  // Check for incorrect result or difference in game state.
	if (result != 0 || memcmp(&pre, post, sizeof(struct gameState)) != 0) {

		// Record errors occuring after shuffle.
		if (shuffled) {

			// TEST - Discard count to high.
			if (pre.discardCount[player] < post->discardCount[player]) {
				errors->numShuffledDiscardErrorsHigh++;
			}

			// TEST - Discard count to low.
			if (pre.discardCount[player] > post->discardCount[player]) {
				errors->numShuffledDiscardErrorsLow++;
			}

			// TEST - Deck count to high.
			if (pre.deckCount[player] < post->deckCount[player]) {
				errors->numShuffledDeckErrorsHigh++;
			}

			// TEST - Deck count to low.
			if (pre.deckCount[player] > post->deckCount[player]) {
				errors->numShuffledDeckErrorsLow++;
			}

			// TEST - Hand count to high.
			if (pre.handCount[player] < post->handCount[player]) {
				errors->numShuffledHandCountErrorsHigh++;
			}

			// TEST - Hand count to low.
			if (pre.handCount[player] > post->handCount[player]) {
				errors->numShuffledHandCountErrorsLow++;
			}

			// TEST - Discard called on Smithy.
			if (pre.playedCards[pre.playedCardCount - 1] != post->playedCards[post->playedCardCount - 1]) {
				errors->numShuffledSmithyDiscardErrors++;
			}

  		// TEST - Player 2 state unchanged.
			if ((memcmp(post->hand[player2], initialPre.hand[player2], sizeof (int) * initialPre.handCount[player]) != 0) ||
			    (memcmp(post->deck[player2], initialPre.deck[player2], sizeof (int) * initialPre.deckCount[player]) != 0) ||
			    (memcmp(post->discard[player2], initialPre.discard[player2], sizeof (int) * initialPre.discardCount[player]) != 0)) {
				errors->numShuffledOtherPlayerStateErrors++;
			}

  		// TEST - Victory card pile unchanged.
			if (initialPre.supplyCount[estate] != post->supplyCount[estate] ||
			    initialPre.supplyCount[duchy] != post->supplyCount[duchy] ||
			    initialPre.supplyCount[province] != post->supplyCount[province]) {
				errors->numShuffledVictoryPileErrors++;
			} 

  		// TEST - Supply pile unchanged.
			if (memcmp(initialPre.supplyCount, post->supplyCount, sizeof(int) * (treasure_map + 1)) != 0) {
				errors->numShuffledSupplyPileErrors++;
			}

		// Test errors occuring during no shuffle.
		} else { 

			// TEST - Discard count too high.
			if (pre.discardCount[player] < post->discardCount[player]) {
				errors->numDiscardErrorsHigh++;
			}

			// TEST - Discard count too low.
			if (pre.discardCount[player] > post->discardCount[player]) {
				errors->numDiscardErrorsLow++;
			}

			// TEST - Deck count too high.
			if (pre.deckCount[player] < post->deckCount[player]) {
				errors->numDeckErrorsHigh++;
			}

			// TEST - Deck count too low.
			if (pre.deckCount[player] > post->deckCount[player]) {
				errors->numDeckErrorsLow++;
			}

			// TEST - Hand count too high.
			if (pre.handCount[player] < post->handCount[player]) {
				errors->numHandCountErrorsHigh++;
			}

			// TEST - Hand count too low.
			if (pre.handCount[player] > post->handCount[player]) {
				errors->numHandCountErrorsLow++;
			}

			// TEST - Discard called on smithy.
			if (pre.playedCards[pre.playedCardCount - 1] != post->playedCards[post->playedCardCount - 1]) {
				errors->numSmithyDiscardErrors++;
			}

  		// TEST - Player 2 state unchanged.
			if ((memcmp(post->hand[player2], initialPre.hand[player2], sizeof (int) * initialPre.handCount[player]) != 0) ||
			    (memcmp(post->deck[player2], initialPre.deck[player2], sizeof (int) * initialPre.deckCount[player]) != 0) ||
			    (memcmp(post->discard[player2], initialPre.discard[player2], sizeof (int) * initialPre.deckCount[player]) != 0)) {
				errors->numOtherPlayerStateErrors++;
			}

  		// TEST - Victory card pile unchanged.
			if (initialPre.supplyCount[estate] != post->supplyCount[estate] ||
			    initialPre.supplyCount[duchy] != post->supplyCount[duchy] ||
			    initialPre.supplyCount[province] != post->supplyCount[province]) {
				errors->numVictoryPileErrors++;
			} 

  		// TEST - Supply pile unchanged.
			if (memcmp(initialPre.supplyCount, post->supplyCount, sizeof(int) * (treasure_map + 1)) != 0) {
				errors->numSupplyPileErrors++;
			}
		}	
	}

	return 1;
}

int main() {
	const int NUM_ITERATIONS = 10000;
	const int MIN_PLAYERS = 2;
	const int MAX_VICTORY_NUM = 12;

	int n, i, player, handPos;

	// Initialize all error counts to 0.
	struct ErrorList errors = {0};
	struct gameState game;

	// Set new seed for each iteration. Needed because PutSeed is called in the
	// test oracle. New seed ensures that different random values will be generated.
	int seed[NUM_ITERATIONS];

	for (i = 0; i < NUM_ITERATIONS; i++) {
		seed[i] = i + 1;
	}

	for (n = 0; n < NUM_ITERATIONS; n++) {
		SelectStream(2);
		PutSeed(seed[n]);

		// Initialize random game state.		
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&game)[i] = floor(Random() * 256);
		}

		// Reset handPos for each iteration.
		handPos = 0;

		// Minimum 2 players.
		game.numPlayers = floor(Random() * (MAX_PLAYERS - MIN_PLAYERS) + MIN_PLAYERS);

		player = floor(Random() * game.numPlayers);

		game.whoseTurn = player;

		// Reserve 1 space for smithy card.
		game.deckCount[player] = floor(Random() * (MAX_DECK - 1));

		// Subtract deckCount to ensure that MAX_DECK property is not violated.
		// Subtract one to reserve space for smithy card.
		game.discardCount[player] = floor(Random() * (MAX_DECK - 1 - 
		                                              game.deckCount[player]));

		// Subtract both deckCount and discardCount to ensure that MAX_DECK property
		// is not violated.
		// Subtract 1 to reserve space for smithy card.
		game.handCount[player] = floor((Random() * (MAX_HAND - 1 -
		                                            game.deckCount[player] - 
		                                            game.discardCount[player])) + 1);

		// Reserve one space for discard of smithy card.
		game.playedCardCount = floor(Random() * (MAX_DECK - 1));

		// Random position in hand for smithy.
		handPos = floor(Random() * game.handCount[player]);
		game.hand[player][handPos] = smithy;

		// Generate random number of victory card pile sizes in supplyCount.
		game.supplyCount[estate] = floor(Random() * MAX_VICTORY_NUM); 
		game.supplyCount[duchy] = floor(Random() * MAX_VICTORY_NUM);
		game.supplyCount[province] = floor(Random() * MAX_VICTORY_NUM);

		// Call test oracle. Stores error counts in &errors.
		checkSmithy(&game, player, handPos, seed[n], &errors);
	}

	printf("Errors given deck shuffled.\n");

	printf("Num errors where hand size is too high: %d\n", 
	       errors.numShuffledHandCountErrorsHigh);

	printf("Num errors where hand size is too low: %d\n", 
	       errors.numShuffledHandCountErrorsLow);

	printf("Num errors where deck size is too high: %d\n", 
	       errors.numShuffledDeckErrorsHigh);

	printf("Num errors where deck size is too low: %d\n", 
	       errors.numShuffledDeckErrorsLow);

	printf("Num errors where discard pile size is too high: %d\n", 
	       errors.numShuffledDiscardErrorsHigh);

	printf("Num errors where discard pile size is too low: %d\n", 
	       errors.numShuffledDiscardErrorsLow);

	printf("Num errors where Smithy card was not discarded: %d\n", 
	       errors.numShuffledSmithyDiscardErrors);

	printf("Num Errors where other players game state is incorrectly changed: %d\n", 
	       errors.numShuffledOtherPlayerStateErrors);

	printf("Num errors, victory card pile changed: %d\n", 
	       errors.numShuffledVictoryPileErrors);

	printf("Num errors, supply pile changed: %d\n", 
	       errors.numShuffledSupplyPileErrors);

	printf("\nErrors occuring given deck not shuffled.\n");

	printf("Num errors where hand size is too high: %d\n", 
	       errors.numHandCountErrorsHigh);

	printf("Num errors where hand size is too low: %d\n", 
	       errors.numHandCountErrorsLow);

	printf("Num errors where deck size is too high: %d\n", 
	       errors.numDeckErrorsHigh);

	printf("Num errors where deck size is too low: %d\n", 
	       errors.numDeckErrorsLow);

	printf("Num errors where discard pile size is too high: %d\n", 
	       errors.numDiscardErrorsHigh);

	printf("Num errors where discard pile size is too low: %d\n", 
	       errors.numDiscardErrorsLow);

	printf("Num errors where Smithy card was not discarded: %d\n", 
	       errors.numSmithyDiscardErrors);

	printf("Num Errors where other players game state is incorrectly changed: %d\n", 
	       errors.numOtherPlayerStateErrors);

	printf("Num errors, victory card pile changed: %d\n", 
	       errors.numVictoryPileErrors);

	printf("Num errors, supply pile changed: %d\n", errors.numSupplyPileErrors);

	return 0;
}