/* ****************************************************
Name: Justin Clarke
Date: 5/5/19
Class: CS362
Assignment: Assignment 3
Description: Card test for Smithy card
NOTE: code adapted from provided examples
*******************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"


// function to compare 2 integers for test result and expected value
int compareInt(int a, int b) {
	if (a == b) {
		printf("***** PASS *****\n");
	}
	else {
	printf("***** FAIL *****\n");
	}
	return 0;
}


// main function for testing Smithy card
int main() {
	
	printf("\n********** Testing Smithy Card **********\n\n");
	int seed = 1000;
    int numPlayer = 2;
    int thisPlayer = 0, otherPlayer = 1;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    // initialize other player's hand due to bug in intializeGame
    G.hand[otherPlayer][0] = copper;
	G.hand[otherPlayer][1] = copper;
	G.hand[otherPlayer][2] = copper;
	G.hand[otherPlayer][3] = estate;
	G.hand[otherPlayer][4] = estate;
	G.handCount[otherPlayer] = 5;

    // copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("Test deck count: %d\n", testG.deckCount[thisPlayer]);
	printf("%d\n", G.deckCount[thisPlayer]);

	// call card effect
	cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);

	// test number of coins
	printf("Coins: %d, Expected: %d ", testG.coins, G.coins);
	compareInt(testG.coins, G.coins);

	// test deck count
	printf("Deck count: %d, Expected %d ", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
	compareInt(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);

	// test other player's deck count
	printf("Other player's deck count: %d, Expected %d ", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
	compareInt(testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);

	// test discard count:
	printf("Discard count: %d, Expected: %d ", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
	compareInt(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);

	// reset the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call card effect with choice1 = 1
	cardEffect(smithy, 1, choice2, choice3, &testG, handPos, &bonus);

	// test number of new cards
	// note: expect 2 new cards after drawing 3 and discarding smithy
	printf("New cards: %d, Expected: %d ", testG.handCount[thisPlayer] - G.handCount[thisPlayer], 2);
	compareInt(testG.handCount[thisPlayer] - G.handCount[thisPlayer], 2);

	// test that new cards came from current player's deck
	printf("New deckCount: %d, Expected: %d ", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
	compareInt(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);

	printf("\n********** Done Testing Smithy Card **********\n\n");
}



