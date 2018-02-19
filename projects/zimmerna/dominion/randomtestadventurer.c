/********************************************************************
** Program name: randomtestcard2.c
** Author: Nathan Zimmerman
** Date: 02/18/2018
** Description: Adventurer random test generator. Use make randomtestadventurer.out
to generate .out file. Or use make randomtestadventurer and then ./randomtestadventurer
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
  // Shuffled Errors.
  int numShuffledDeckErrorsHigh;
  int numShuffledDeckErrorsLow;
  int numShuffledHandCountErrorsHigh;
  int numShuffledHandCountErrorsLow;
  int numShuffledDiscardErrorsHigh;
  int numShuffledDiscardErrorsLow;
  int numShuffledHandTreasureErrors;
  int numShuffledDeckTreasureErrors;
  int numShuffledDiscardTreasureErrors;
  int numShuffledOtherPlayerStateErrors;
  int numShuffledVictoryPileErrors;
  int numShuffledSupplyPileErrors;

  // No Shuffle Errors.
  int numDeckErrorsHigh;
  int numDeckErrorsLow;
  int numHandCountErrorsHigh;
  int numHandCountErrorsLow;
  int numDiscardErrorsHigh;
  int numDiscardErrorsLow;
  int numHandTreasureErrors;
  int numDeckTreasureErrors;
  int numDiscardTreasureErrors;
  int numOtherPlayerStateErrors;
  int numVictoryPileErrors;
  int numSupplyPileErrors;
};

// Counts treasures in hand.
int treasureHandCount(struct gameState *state, int player) {
	int treasureCount = 0;
	int i;

	for (i = 0; i < state->handCount[player]; i++) {
		if (state->hand[player][i] == copper || state->hand[player][i] == silver ||
				state->hand[player][i] == gold) {
			treasureCount++;
		}
	}

	return treasureCount;
}

// Counts treasures in deck.
int treasureDeckCount(struct gameState *state, int player) {
	int treasureCount = 0;
	int i;

	for (i = 0; i < state->deckCount[player]; i++) {
		if (state->deck[player][i] == copper || state->deck[player][i] == silver ||
				state->deck[player][i] == gold) {
			treasureCount++;
		}
	}

	return treasureCount;
}

// Counts treasures in discard pile.
int treasureDiscardCount(struct gameState *state, int player) {
	int treasureCount = 0;
	int i;

	for (i = 0; i < state->discardCount[player]; i++) {
		if (state->discard[player][i] == copper || state->discard[player][i] == silver ||
				state->discard[player][i] == gold) {
			treasureCount++;
		}
	}

	return treasureCount;
}

int checkAdventurer(struct gameState *post, int player, int handPos, int seed, 
                    struct ErrorList* errors) {

  // Store result of cardEffect call.
	int result;

  // Flag set when deck is shuffled.
	int shuffled = 0;

	int bonus = 0;
  int drawnTreasure = 0;
	int preTreasureCount = 0;
	int postTreasureCount = 0;
	int cardDrawn;
	int temphand[MAX_HAND];
	int z = 0;
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
	
	result = cardEffect(adventurer, -1, -1, -1, post, handPos, &bonus);

  // Simulate correct adventurer behavior.
	while (drawnTreasure < 2) {
    // Check for shuffle. Call PutSeed to reset seed so that shuffle is the
    // same for simulated behavior as it is for cardEffect call.
    if (pre.deckCount[player] < 1) {
    	SelectStream(2);
			PutSeed(seed); 

			// If the deck is empty we need to shuffle discard and add to deck
    	shuffle(player, &pre);

      // Set shuffled flag to divide errors into shuffled and non-shuffled.
    	shuffled = 1;
    }

    drawCard(player, &pre);
    cardDrawn = pre.hand[player][pre.handCount[player] - 1]; //top card of hand is most recently drawn card.

    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
    	drawnTreasure++;
    else {
    	temphand[z] = cardDrawn;
      pre.handCount[player]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }

  while (z - 1 >= 0) {
    pre.discard[player][pre.discardCount[player]++] = temphand[z - 1]; // discard all cards in play that have been drawn
    z = z - 1;
  }

  // Discard adventurer card.
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

			// TEST - Treasures in hand.
  		preTreasureCount = treasureHandCount(&pre, player);
  		postTreasureCount = treasureHandCount(post, player);

  		if (preTreasureCount != postTreasureCount) {
  			errors->numShuffledHandTreasureErrors++;
  		}

      // TEST - Treasures in discard.
  		preTreasureCount = treasureDiscardCount(&pre, player);
  		postTreasureCount = treasureDiscardCount(post, player);

  		if (preTreasureCount != postTreasureCount) {
  			errors->numShuffledDiscardTreasureErrors++;
  		}

      // TEST - Treasures in deck.
  		preTreasureCount = treasureDeckCount(&pre, player);
  		postTreasureCount = treasureDeckCount(post, player);

  		if (preTreasureCount != postTreasureCount) {
  			errors->numShuffledDeckTreasureErrors++;
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

			// TEST - Treasures in hand.
  		preTreasureCount = treasureHandCount(&pre, player);
  		postTreasureCount = treasureHandCount(post, player);

  		if (preTreasureCount != postTreasureCount) {
  			errors->numHandTreasureErrors++;
  		}

      // TEST - Treasures in discard.
  		preTreasureCount = treasureDiscardCount(&pre, player);
  		postTreasureCount = treasureDiscardCount(post, player);

  		if (preTreasureCount != postTreasureCount) {
  			errors->numDiscardTreasureErrors++;
  		}

      // TEST - Treasures in deck.
  		preTreasureCount = treasureDeckCount(&pre, player);
  		postTreasureCount = treasureDeckCount(post, player);

  		if (preTreasureCount != postTreasureCount) {
  			errors->numDeckTreasureErrors++;
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
	// Treasure amount character starts with.
	const int TREASURE_MIN = 7;
	const int SILVER_MAX = 40;
	const int GOLD_MAX = 30;
  const int NUM_ITERATIONS = 10000;
  const int MIN_PLAYERS = 2;
  const int MAX_VICTORY_NUM = 12;

  // Depends on number of players. Set after numPlayers is set.
	int copperMax;

  // Initialize all error counts to zero.
  struct ErrorList errors = {0};
  struct gameState game;

	int n, i, player, numCopper, numSilver, numGold, totalTreasure;

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

   	int handPos = 0;
		int deckPos = 0;
		int discardPos = 0;
		int treasureNeeded = 0;

    // Minimum 2 players.
    game.numPlayers = floor(Random() * (MAX_PLAYERS - MIN_PLAYERS) + MIN_PLAYERS);

    player = floor(Random() * game.numPlayers);

    game.whoseTurn = player;

    // Reset everything for new iteration.
    game.handCount[player] = 0;
    game.deckCount[player] = 0;
    game.discardCount[player] = 0;

    // Copper max calculation taken from dominion.h
    copperMax = 60 - (7 * game.numPlayers);

    numCopper = floor(Random() * copperMax);
    numSilver = floor(Random() * SILVER_MAX);

    // Minimum treasure needed to avoid adventurer infinite loop. 7 selected
    // as that is the treasure amount in starting deck.
    treasureNeeded = TREASURE_MIN - (numCopper + numSilver);

    if (treasureNeeded < 0) {
    	treasureNeeded = 0;
    }

    // Random amount, taking into account minimum treasure needed to avoid infinite
    // loop in adventurer.
    numGold = floor(Random() * (GOLD_MAX - treasureNeeded) + treasureNeeded);

    totalTreasure = numCopper + numSilver + numGold;

    // Place coins randomly in either deck of discard. Position randomized later.
    for (i = 0; i < totalTreasure; i++) {
    	int deckChoice = floor(Random() * 2);
    	int coinChoice;

    	if (numCopper > 0) {
    		coinChoice = copper;
    		numCopper--;
    	} else if (numSilver > 0) {
    		coinChoice = silver;
    		numSilver--;
    	} else {
    		coinChoice = gold;
    		numGold--;
    	}

    	switch (deckChoice) {
    		case 0: {
    			game.deck[player][deckPos] = coinChoice;

    			game.deckCount[player]++;

    			deckPos++;

    			break;
    		}
    		case 1: {
    			game.discard[player][discardPos] = coinChoice;

    			game.discardCount[player]++;

    			discardPos++;

    			break;
    		}
    	}
    }

    // Generate random size taking into account amount already taken
    // by coins in deck and discard. Also 1 spot reserved for adventurer card.
    game.deckCount[player] = floor(Random() * (MAX_DECK - 1 -
    															 game.deckCount[player] -
    															 game.discardCount[player]) + 
    															 game.deckCount[player]);

    // Generate random size taking into account amount already taken
    // by coins in deck and discard. Also 1 spot reserved for adventurer card.
    game.discardCount[player] = floor(Random() * (MAX_DECK - 1 - 
    																	game.deckCount[player] - 
    																	game.discardCount[player]) + 
    																	game.discardCount[player]);

    // Generate random size taking into account amount already in
    // deck and discard to ensure MAX_HAND property not violated.
    game.handCount[player] = floor((Random() * (MAX_HAND - 1 -
    																game.deckCount[player] - 
    																game.discardCount[player])) + 1);

    // Reserve one space for discard of adventurer card.
    game.playedCardCount = floor(Random() * (MAX_DECK - 1));

    // Randomize position of cards in hand.
    for (i = 0; i < game.handCount[player]; i++) {
    	int swapIndex = floor(Random() * game.handCount[player]);

    	int temp = game.hand[player][i];
    	game.hand[player][i] = game.hand[player][swapIndex];
    	game.hand[player][swapIndex] = temp;
    }

    // Randomize position of cards in deck.
    for (i = 0; i < game.deckCount[player]; i++) {
    	int swapIndex = floor(Random() * game.deckCount[player]);

    	int temp = game.deck[player][i];
    	game.deck[player][i] = game.deck[player][swapIndex];
    	game.deck[player][swapIndex] = temp;
    }

    // Randomize position of cards in discard pile.
    for (i = 0; i < game.discardCount[player]; i++) {
    	int swapIndex = floor(Random() * game.discardCount[player]);

    	int temp = game.discard[player][i];
    	game.discard[player][i] = game.discard[player][swapIndex];
    	game.discard[player][swapIndex] = temp;
    }

    // Find random position for adventurer in hand that is not taken by a coin.
    do {
    	handPos = floor(Random() * game.handCount[player]);
    } while(game.hand[player][handPos] == copper || 
          	game.hand[player][handPos] == silver ||
          	game.hand[player][handPos] == gold);

    // Random position in hand for adventurer.
    game.hand[player][handPos] = adventurer;

    // Generate random number of victory card pile sizes in supplyCount.
    game.supplyCount[estate] = floor(Random() * MAX_VICTORY_NUM); 
    game.supplyCount[duchy] = floor(Random() * MAX_VICTORY_NUM);
    game.supplyCount[province] = floor(Random() * MAX_VICTORY_NUM);

    // Test oracle function.
    checkAdventurer(&game, player, handPos, seed[n], &errors);
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

	printf("Num errors where hand treasure count different than expected: %d\n", 
         errors.numShuffledHandTreasureErrors);

	printf("Num errors where deck treasure count different than expected: %d\n", 
         errors.numShuffledDeckTreasureErrors);

	printf("Num errors where discard pile treasure count different than expected: %d\n", 
         errors.numShuffledDiscardTreasureErrors);

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

	printf("Num errors where hand treasure count different than expected: %d\n", 
         errors.numHandTreasureErrors);

	printf("Num errors where deck treasure count different than expected: %d\n", 
         errors.numDeckTreasureErrors);

	printf("Num errors where discard pile treasure count different than expected: %d\n", 
         errors.numDiscardTreasureErrors);

	printf("Num Errors where other players game state is incorrectly changed: %d\n", 
         errors.numOtherPlayerStateErrors);

	printf("Num errors, victory card pile changed: %d\n", 
         errors.numVictoryPileErrors);

	printf("Num errors, supply pile changed: %d\n", 
         errors.numSupplyPileErrors);

	return 0;
}