/********************************************************************
** Program name: cardtest4
** Author: Nathan Zimmerman
** Date: 02/04/2018
** Description: Unit test for mine card function playVillage()
how to run it: make unittestresults.out or make cardtest4 and then
./cardtest4
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
  int playerHand[6] = {copper, silver, gold, mine, adventurer, estate};
  int playerHandSize = 6;
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
               village, baron, great_hall};
  int bonus = 0;
  int handPos = 3;
  int cardFound;
  struct gameState game, testGame, preTestGame;
  int numSilver = 0;
  int minePresent;

  printf("-- Testing mine -- \n\n");

  // TEST 1
  printf(YELLOW "Testing player choice 1 is not a treasure card.\n" RESET);

  // Clear game state and initialize new game.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  // Set hand contents equal to playerHand selection.
  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  // Set all states so that they use the playerHand selection.
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  // Select invalid card choices using playerHand.
  returnVal = cardEffect(mine, 4, gold, -1, &testGame, handPos, &bonus);
  printf("Choice 1 = adventurer, Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  // Clear state and re-initialize so that function can be called again.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  // Set hand again.
  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  // Checks against different invalid card.
  returnVal = cardEffect(mine, 5, gold, -1, &testGame, handPos, &bonus);
  printf("Choice 1 = estate, Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  printf("\n");

  // TEST 2
  printf(YELLOW "Testing player choice 2 is not a treasure card.\n" RESET);

  // Clear state and re-initialize so that function can be called again.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  // Checking invalid second choice using card from playerHand.
  returnVal = cardEffect(mine, 0, adventurer, -1, &testGame, handPos, &bonus);
  printf("Choice 2 = adventurer, Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  // Clear state and re-initialize so that function can be called again.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  // Second test looks to trigger a different invalid choice based on the conditional
  // statements present in the mine card.
  returnVal = cardEffect(mine, 0, estate, -1, &testGame, handPos, &bonus);
  printf("Choice 2 = estate, Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  printf("\n");

  // TEST 3
  printf(YELLOW "Testing player choice 2 is not a valid card number.\n" RESET);

  // Clear state and re-initialize so that function can be called again.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  // Values are meant to trigger a different condition in the mine card. Tests
  // invalid card numbers.
  returnVal = cardEffect(mine, 0, -1, -1, &testGame, handPos, &bonus);
  printf("Choice 2 = -1, Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  // Clear state and re-initialize so that function can be called again.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  // Values are meant to trigger a different condition in the mine card. Tests
  // invalid card numbers.
  returnVal = cardEffect(mine, 0, -1, 30, &testGame, handPos, &bonus);
  printf("Choice 2 = 30, Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  printf("\n");

  // TEST 4
  printf(YELLOW "Testing player choice 2 costs up to 3 more.\n" RESET);

  // Clear state and re-initialize so that function can be called again.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  // Valid card used for this test.
  returnVal = cardEffect(mine, 0, silver, -1, &testGame, handPos, &bonus);

  // Valid card behavior simulated.
  game.handCount[player]++;
  game.hand[player][game.handCount[player] - 1] = silver;

  printf("Choice 2 = silver, Function return value = %d, Expected = %d. ", returnVal, 0);
  assertTest(returnVal == 0);

  // Compare correct simulated behavior to function call by comparing game states.
  printf("Card at last hand position = %d, Expected = %d. ", testGame.hand[player][testGame.handCount[player] - 1], 
         game.hand[player][game.handCount[player] - 1]);
  assertTest(testGame.hand[player][testGame.handCount[player] - 1] == game.hand[player][game.handCount[player] - 1]);

  printf("\n");

  // TEST 5
  printf(YELLOW "Testing player choice 2 costs more than 3.\n" RESET);

  // Clear state and re-initialize so that function can be called again.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  // Invalid difference in cost.
  returnVal = cardEffect(mine, 0, gold, -1, &testGame, handPos, &bonus);

  printf("cardEffect return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  printf("\n");

  // TEST 6
  printf(YELLOW "Testing gained card added to hand.\n" RESET);

  // Clear state and re-initialize so that function can be called again.
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  cardEffect(mine, 0, silver, -1, &testGame, handPos, &bonus);

  // Simulate adding card to hand.
  game.handCount[player]++;
  game.hand[player][game.handCount[player] - 1] = silver;

  // Both mine card and trashed treasure card should be discarded.
  discardCard(handPos, player, &game, 0);
  discardCard(0, player, &game, 1);

  // Check if card is present in hand after function call.
  for (i = 0; i < playerHandSize; i++) {
    if (testGame.hand[player][i] == silver) {
      numSilver++;
    }
  }

  // Card should stay in hand as it was just gained.
  if (numSilver == 2) {
    printf("Choice 2 found at hand position %d. ", i);
    assertTest(1);
  } else {
    printf("Choice 2 not found. ");
    assertTest(0);
  }

  // Compare simulated behavior to that of function call.
  printf("Card at last hand position = %d, Expected = %d. ", testGame.hand[player][testGame.handCount[player] - 1], 
         game.hand[player][game.handCount[player] - 1]);
  assertTest(testGame.hand[player][testGame.handCount[player] - 1] == game.hand[player][game.handCount[player] - 1]);

  // Checks for correct number of discards.
  printf("Hand count = %d, Expected = %d. ", testGame.handCount[player], game.handCount[player]);
  assertTest(testGame.handCount[player] == game.handCount[player]);

  printf("\n");

  // TEST 7
  printf(YELLOW "Testing choice 1 is trashed.\n" RESET);
  
  // Search for card that is supposed to be trashed.
  for (i = 0; i < playerHandSize; i++) {
    if (testGame.hand[player][i] == copper) {
      cardFound = 1;
    }
  }

  // Card should not be in hand.
  if (cardFound == 1) {
    printf("Choice 1 found at hand position %d. ", i);
    assertTest(0);
  } else {
    printf("Choice 1 not found. ");
    assertTest(1);
  }

  printf("\n");

  // TEST 8
  printf(YELLOW "Testing player calls discardCard on mine card after use.\n" RESET);

  // discardCard should be called because mine should be added to the played pile.
  printf("Top played card value = %d, Expected = %d. ", 
         testGame.playedCards[testGame.playedCardCount - 1], 
         game.playedCards[game.playedCardCount - 1]);
  assertTest(testGame.playedCards[testGame.playedCardCount - 1] == game.playedCards[game.playedCardCount - 1]);

  for (i = 0; i < testGame.playedCardCount - 1; i++) {
    if (testGame.playedCards[i] == mine) {
      minePresent = 1;
    }
  }

  if (minePresent) {
    printf("Mine present in played pile: ");
    assertTest(1);
  } else {
    printf("Mine card not present in played pile: ");
    assertTest(0);
  }

  printf("\n");

  // TEST 9
  printf(YELLOW "Testing no state change for other players.\n" RESET);

  // Player2 state should not change since function is called for player1.
  printf("Hand for player 2 remains the same: ");
  assertTest(memcmp(game.hand[player2], testGame.hand[player2], sizeof (int) * player2HandSize) == 0);

  printf("Deck for player 2 remains the same: ");
  assertTest(memcmp(game.deck[player2], testGame.deck[player2], sizeof (int) * player2HandSize) == 0);

  printf("Discard pile for player 2 remains the same: ");
  assertTest(memcmp(game.discard[player2], testGame.discard[player2], sizeof (int) * player2HandSize) == 0);

  printf("\n");

  // TEST 10
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

  // TEST 11
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