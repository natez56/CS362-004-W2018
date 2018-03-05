/********************************************************************
** Program name: cardtest2
** Author: Nathan Zimmerman
** Date: 02/04/2018
** Description: Unit test for adventurer card function playAdventurer()
how to run it: make unittestresults.out or make cardtest2 and then
./cardtest2
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
  int drawnTreasure = 0;
	int seed = 1000;
  int numPlayers = 2;
  int player = 0;
  int player2 = 1;
  int player2HandSize = 5;
  int testDeck[6] = {feast, gold, copper, adventurer, feast, silver};
  int testDeckSize = 6;
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
               village, baron, great_hall};
  int bonus = 0;
  int handPos = 0;
  int testCardsDrawn = 0;
  int cardsDrawn = 0;
  int testGameTreasuresDrawn = 0;
  struct gameState game, testGame, preTestGame;

  printf("-- Testing adventurer -- \n\n");

  // TEST 1
  printf(YELLOW "Testing player draws until 2 treasures no shuffle.\n" RESET);

  // Clear game state and initialize new game.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  // Set game deck equal to testDeck values.
  game.handCount[player] = 0;
  game.deckCount[player] = testDeckSize;

  for (i = 0; i < testDeckSize; i++) {
    game.deck[player][i] = testDeck[i];
  }
  
  // Set test game states to equal to state of game. All gameState structs
  // using test deck values.
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));
  
  cardEffect(adventurer, -1, -1, -1, &testGame, handPos, &bonus);

  // Simulate behavior of adventurer card effect. Drawing cards until number of
  // treasures = 2.
  while (drawnTreasure < 2) {
    drawCard(player, &game);
    cardsDrawn++;
    int cardDrawn = game.hand[player][game.handCount[player] - 1];

    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
      drawnTreasure++;
    }
  }

  // Get number of cards and number of treasures drawn to ensure that correct amount
  // was drawn during function call.
  testCardsDrawn = preTestGame.deckCount[player] - testGame.deckCount[player];

  for (i = 0; i < testGame.handCount[player]; i++) {
    if (testGame.hand[player][i] == copper || testGame.hand[player][i] == silver || testGame.hand[player][i] == gold) {
      testGameTreasuresDrawn++;
    }
  }

  // Compare function result to manually altered game state.
  printf("Number of drawn cards = %d, Expected = %d. ", testCardsDrawn, cardsDrawn);
  assertTest(testCardsDrawn == cardsDrawn);

  printf("Number of treasures drawn = %d, Expected = %d. ", testGameTreasuresDrawn, drawnTreasure);
  assertTest(testGameTreasuresDrawn == drawnTreasure);

  printf("\n");

  // TEST 2
  printf(YELLOW "Testing player draws until 2 treasures with shuffle.\n" RESET);

  // Clear game state and and re-initialize.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  // Set deck count to zero so that shuffle is triggered.
  game.deckCount[player] = 0;
  game.handCount[player] = 0;
  game.discardCount[player] = testDeckSize;

  for (i = 0; i < testDeckSize; i++) {
    game.discard[player][i] = testDeck[i];
  }

  // Copy current deck set up to all game states.
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  cardEffect(adventurer, -1, -1, -1, &testGame, handPos, &bonus);

  // Get testGame number of treasures drawn.
  testGameTreasuresDrawn = 0;
  for (i = 0; i < testGame.handCount[player]; i++) {
    if (testGame.hand[player][i] == copper || testGame.hand[player][i] == silver || testGame.hand[player][i] == gold) {
      testGameTreasuresDrawn++;
    }
  }

  // Compare the number of treasures to the correct number 2.
  printf("Number of treasures drawn = %d, Expected = %d. ", testGameTreasuresDrawn, 2);
  assertTest(testGameTreasuresDrawn == 2);

  printf("\n");

  // TEST 3
  printf(YELLOW "Testing player discards non-treasure cards from hand.\n" RESET);

  // Clear game state and and re-initialize.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  // Set game state so that shuffle does not trigger.
  game.handCount[player] = 1;
  game.deckCount[player] = testDeckSize;

  for (i = 0; i < testDeckSize; i++) {
    game.deck[player][i] = testDeck[i];
  }
  
  // Set same deck for all game states.
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  cardEffect(adventurer, -1, -1, -1, &testGame, handPos, &bonus);

  // Simulate correct card behavior for game.
  drawnTreasure = 0;
  cardsDrawn = 0;
  while (drawnTreasure < 2) {
    drawCard(player, &game);
    cardsDrawn++;
    int cardDrawn = game.hand[player][game.handCount[player] - 1];

    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
      drawnTreasure++;
    }
  }

  discardCard(handPos, player, &game, 0);

  // Compare correct simulated behavior with function call.
  printf("Number of cards in hand = %d, Expected = %d. ", testGame.handCount[player], cardsDrawn - drawnTreasure);
  assertTest(testGame.handCount[player] == cardsDrawn - drawnTreasure);

  printf("\n");

  // TEST 4
  printf(YELLOW "Testing drawn cards come from player's own pile.\n" RESET);

  // Compare state of testGame prior to function call to ensure that cards are coming form correct deck.
  cardsDrawn = preTestGame.deckCount[player] - testGame.deckCount[player];
  printf("Deck count = %d, Expected = %d. ", testGame.deckCount[player], preTestGame.deckCount[player] - cardsDrawn);
  assertTest(testGame.deckCount[player] == preTestGame.deckCount[player] - cardsDrawn);

  printf("\n");

  // TEST 5
  printf(YELLOW "Testing player calls discardCard on adventurer card after use.\n" RESET);

  // Make sure that adventurer is added to the played pile through the use of the discardCard function.
  printf("Top played card value = %d, Expected = %d. ", 
         testGame.playedCards[testGame.playedCardCount - 1], 
         game.playedCards[game.playedCardCount - 1]);
  assertTest(testGame.playedCards[testGame.playedCardCount - 1] == game.playedCards[game.playedCardCount - 1]);

  printf("\n");

  // TEST 6
  printf(YELLOW "Testing no state change for other players.\n" RESET);

  // Player2 state should not change since function is called for player1.
  printf("Hand for player 2 remains the same: ");
  assertTest(memcmp(game.hand[player2], testGame.hand[player2], sizeof (int) * player2HandSize) == 0);

  printf("Deck for player 2 remains the same: ");
  assertTest(memcmp(game.deck[player2], testGame.deck[player2], sizeof (int) * player2HandSize) == 0);

  printf("Discard pile for player 2 remains the same: ");
  assertTest(memcmp(game.discard[player2], testGame.discard[player2], sizeof (int) * player2HandSize) == 0);

  printf("\n");

  // TEST 7
  printf(YELLOW "Testing no state change to the victory card pile.\n" RESET);

  // Comparing game states for testGame where function is called and game, where
  // behavior is manually simulated.
  printf("Estate pile count = %d, Expected = %d. ", testGame.supplyCount[estate], game.supplyCount[estate]);
  assertTest(testGame.supplyCount[estate] == game.supplyCount[estate]);

  printf("Duchy pile count = %d, Expected = %d. ", testGame.supplyCount[duchy], game.supplyCount[duchy]);
  assertTest(testGame.supplyCount[duchy] == game.supplyCount[duchy]);

  printf("Province pile count = %d, Expected = %d. ", testGame.supplyCount[province], game.supplyCount[province]);
  assertTest(testGame.supplyCount[province] == game.supplyCount[province]);

  printf("\n");

  // TEST 8
  printf(YELLOW "Testing no state change to the kingdom card pile.\n" RESET);

  // Loop counts supply of each kingdom card and compares it to state where playSmithy()
  // is not called.
  for (i = 0; i < 10; i++) {
    printf("Number of card number %d = %d, Expected = %d. ", k[i], testGame.supplyCount[k[i]], game.supplyCount[k[i]]);
    assertTest(testGame.supplyCount[k[i]] == game.supplyCount[k[i]]);
  }

  printf("\n");

  return 0;
}