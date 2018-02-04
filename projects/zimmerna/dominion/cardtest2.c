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

  printf(YELLOW "Testing player draws until 2 treasures no shuffle.\n" RESET);
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = 0;
  game.deckCount[player] = testDeckSize;
  for (i = 0; i < testDeckSize; i++) {
    game.deck[player][i] = testDeck[i];
  }
  
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));
  cardEffect(adventurer, -1, -1, -1, &testGame, handPos, &bonus);

  while (drawnTreasure < 2) {
    drawCard(player, &game);
    cardsDrawn++;
    int cardDrawn = game.hand[player][game.handCount[player] - 1];

    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
      drawnTreasure++;
    }
  }

  testCardsDrawn = preTestGame.deckCount[player] - testGame.deckCount[player];

  for (i = 0; i < testGame.handCount[player]; i++) {
    if (testGame.hand[player][i] == copper || testGame.hand[player][i] == silver || testGame.hand[player][i] == gold) {
      testGameTreasuresDrawn++;
    }
  }
  printf("Number of drawn cards = %d, Expected = %d. ", testCardsDrawn, cardsDrawn);
  assertTest(testCardsDrawn == cardsDrawn);
  printf("Number of treasures drawn = %d, Expected = %d. ", testGameTreasuresDrawn, drawnTreasure);
  assertTest(testGameTreasuresDrawn == drawnTreasure);

  printf("\n");

  printf(YELLOW "Testing player draws until 2 treasures with shuffle.\n" RESET);
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);
  game.deckCount[player] = 0;
  game.handCount[player] = 0;
  game.discardCount[player] = testDeckSize;
  for (i = 0; i < testDeckSize; i++) {
    game.discard[player][i] = testDeck[i];
  }

  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));
  cardEffect(adventurer, -1, -1, -1, &testGame, handPos, &bonus);

  testGameTreasuresDrawn = 0;
  for (i = 0; i < testGame.handCount[player]; i++) {
    if (testGame.hand[player][i] == copper || testGame.hand[player][i] == silver || testGame.hand[player][i] == gold) {
      testGameTreasuresDrawn++;
    }
  }

  testCardsDrawn = testGame.handCount[player] - preTestGame.handCount[player];
  printf("Number of treasures drawn = %d, Expected = %d. ", testGameTreasuresDrawn, 2);
  assertTest(testGameTreasuresDrawn == 2);

  printf("\n");

  printf(YELLOW "Testing player discards non-treasure cards from hand.\n" RESET);
  memset(&game, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &game);

  game.handCount[player] = 1;
  game.deckCount[player] = testDeckSize;
  for (i = 0; i < testDeckSize; i++) {
    game.deck[player][i] = testDeck[i];
  }
  
  memcpy(&testGame, &game, sizeof(struct gameState));
  memcpy(&preTestGame, &game, sizeof(struct gameState));
  cardEffect(adventurer, -1, -1, -1, &testGame, handPos, &bonus);

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

  printf("Number of cards in hand = %d, Expected = %d. ", testGame.handCount[player], cardsDrawn - drawnTreasure);
  assertTest(testGame.handCount[player] == cardsDrawn - drawnTreasure);

  printf("\n");

  printf(YELLOW "Testing drawn cards come from player's own pile.\n" RESET);
  cardsDrawn = preTestGame.deckCount[player] - testGame.deckCount[player];
  printf("Deck count = %d, Expected = %d. ", testGame.deckCount[player], preTestGame.deckCount[player] - cardsDrawn);
  assertTest(testGame.deckCount[player] == preTestGame.deckCount[player] - cardsDrawn);

  printf("\n");

  printf(YELLOW "Testing player calls discardCard on adventurer card after use.\n" RESET);

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
int playAdventurer(int drawntreasure, struct gameState *state, int currentPlayer, int cardDrawn, int* temphand, int z) {
  while (drawntreasure <= 2) {
    if (state->deckCount[currentPlayer] < 1) { //if the deck is empty we need to shuffle discard and add to deck
      shuffle(currentPlayer, state);
    }

    drawCard(currentPlayer, state);
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1]; //top card of hand is most recently drawn card.

    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      drawntreasure++;
    else {
      temphand[z] = cardDrawn;
      state->handCount[currentPlayer]; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }

  while (z - 1 >= 0) {
    state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1]; // discard all cards in play that have been drawn
    z = z - 1;
  }

  return 0;
}
*/