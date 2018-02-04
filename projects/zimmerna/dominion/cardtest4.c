/********************************************************************
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
  int playerHand[6] = {copper, silver, gold, mine, adventurer, estate};
  int playerHandSize = 6;
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
               village, baron, great_hall};
  int bonus = 0;
  int handPos = 3;
  int cardFound;
  
  
  struct gameState game, testGame, preTestGame;

  printf("-- Testing mine -- \n\n");

  printf(YELLOW "Testing player choice 1 is not a treasure card.\n" RESET);

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  returnVal = cardEffect(mine, 4, 2, -1, &testGame, handPos, &bonus);
  printf("Choice 1 = adventurer, Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  returnVal = cardEffect(mine, 5, 2, -1, &testGame, handPos, &bonus);
  printf("Choice 1 = estate, Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  printf("\n");

  printf(YELLOW "Testing player choice 2 is not a treasure card.\n" RESET);

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  returnVal = cardEffect(mine, 0, 4, -1, &testGame, handPos, &bonus);
  printf("Choice 2 = adventurer, Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  returnVal = cardEffect(mine, 0, 5, -1, &testGame, handPos, &bonus);
  printf("Choice 2 = estate, Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  printf("\n");

  printf(YELLOW "Testing player choice 2 is not a valid card number.\n" RESET);
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  returnVal = cardEffect(mine, 0, -1, -1, &testGame, handPos, &bonus);
  printf("Choice 2 = -1, Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  returnVal = cardEffect(mine, 0, -1, 30, &testGame, handPos, &bonus);
  printf("Choice 2 = 30, Function return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  printf("\n");

  printf(YELLOW "Testing player choice 2 costs up to 3 more.\n" RESET);

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  cardEffect(mine, 0, 1, -1, &testGame, handPos, &bonus);

  game.handCount[player]++;
  game.hand[player][game.handCount[player] - 1] = silver;

  printf("Card at last hand position = %d, Expected = %d. ", testGame.hand[player][testGame.handCount[player] - 1], 
         game.hand[player][game.handCount[player] - 1]);
  assertTest(testGame.hand[player][testGame.handCount[player] - 1] == game.hand[player][game.handCount[player] - 1]);

  printf("\n");

  printf(YELLOW "Testing player choice 2 costs more than 3.\n" RESET);

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  returnVal = cardEffect(mine, 0, 2, -1, &testGame, handPos, &bonus);

  printf("cardEffect return value = %d, Expected = %d. ", returnVal, -1);
  assertTest(returnVal == -1);

  printf("\n");

  printf(YELLOW "Testing gained card added to hand.\n" RESET);

  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = playerHandSize;
  memcpy(game.hand[player], playerHand, sizeof (int) * playerHandSize);

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));

  cardEffect(mine, 0, 1, -1, &testGame, handPos, &bonus);

  game.handCount[player]++;
  game.hand[player][game.handCount[player] - 1] = silver;
  discardCard(handPos, player, &game, 0);
  discardCard(0, player, &game, 1);

  for (i = 0; i < playerHandSize; i++) {
    if (testGame.hand[player][i] == silver) {
      cardFound = 1;
    }
  }

  if (cardFound == 1) {
    printf("Choice 2 found at hand position %d", i);
    assertTest(1);
  } else {
    printf("Choice 2 not found. ");
    assertTest(0);
  }

  printf("Card at last hand position = %d, Expected = %d. ", testGame.hand[player][testGame.handCount[player] - 1], 
         game.hand[player][game.handCount[player] - 1]);
  assertTest(testGame.hand[player][testGame.handCount[player] - 1] == game.hand[player][game.handCount[player] - 1]);

  printf("Hand count = %d, Expected = %d. ", testGame.handCount[player], game.handCount[player]);
  assertTest(testGame.handCount[player] == game.handCount[player]);

  printf("\n");

  printf(YELLOW "Testing choice 1 is trashed.\n" RESET);
  
  for (i = 0; i < playerHandSize; i++) {
    if (testGame.hand[player][i] == copper) {
      cardFound = 1;
    }
  }

  if (cardFound == 1) {
    printf("Choice 1 found at hand position %d. ", i);
    assertTest(0);
  } else {
    printf("Choice 1 not found. ");
    assertTest(1);
  }

  printf("\n");

  printf(YELLOW "Testing player calls discardCard on mine card after use.\n" RESET);

  printf("Top played card value = %d, Expected = %d. ", 
         testGame.playedCards[testGame.playedCardCount - 1], 
         game.playedCards[game.playedCardCount - 1]);
  assertTest(testGame.playedCards[testGame.playedCardCount - 1] == game.playedCards[game.playedCardCount - 1]);

  printf("\n");

  printf(YELLOW "Testing no state change for other players.\n" RESET);

  printf("Hand for player 2 remains the same: ");
  assertTest(memcmp(game.hand[player2], testGame.hand[player2], sizeof (int) * player2HandSize) == 0);

  printf("Deck for player 2 remains the same: ");
  assertTest(memcmp(game.deck[player2], testGame.deck[player2], sizeof (int) * player2HandSize) == 0);

  printf("Discard pile for player 2 remains the same: ");
  assertTest(memcmp(game.discard[player2], testGame.discard[player2], sizeof (int) * player2HandSize) == 0);

  printf("\n");

  printf(YELLOW "Testing no state change to the victory card pile.\n" RESET);

  printf("Estate pile count = %d, Expected = %d. ", testGame.supplyCount[estate], game.supplyCount[estate]);
  assertTest(testGame.supplyCount[estate] == game.supplyCount[estate]);

  printf("Duchy pile count = %d, Expected = %d. ", testGame.supplyCount[duchy], game.supplyCount[duchy]);
  assertTest(testGame.supplyCount[duchy] == game.supplyCount[duchy]);

  printf("Province pile count = %d, Expected = %d. ", testGame.supplyCount[province], game.supplyCount[province]);
  assertTest(testGame.supplyCount[province] == game.supplyCount[province]);

  printf("\n");

  printf(YELLOW "Testing no state change to the kingdom card pile.\n" RESET);

  for (i = 0; i < 10; i++) {
    printf("Number of card number %d = %d, Expected = %d. ", k[i], testGame.supplyCount[k[i]], game.supplyCount[k[i]]);
    assertTest(testGame.supplyCount[k[i]] == game.supplyCount[k[i]]);
  }

  return 0;
}

/*
int playMine(struct gameState *state, int currentPlayer, int handPos, int choice1, int choice2) {
  int i;
  int j;

  j = state->hand[currentPlayer][choice2];  //store card we will trash

  if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold) {
    return -1;
  }
    
  if (choice2 > treasure_map || choice2 < curse) {
    return -1;
  }

  if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) ) {
    return -1;
  }

  gainCard(choice2, state, 2, currentPlayer);

  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);

  //discard trashed card
  for (i = 0; i < state->handCount[currentPlayer]; i++) {
    if (state->hand[currentPlayer][i] == j) {
      discardCard(i, currentPlayer, state, 0);      
      break;
    }
  }
      
  return 0;  
}
*/