/* ****************************************************
Name: Justin Clarke
Date: 5/5/19
Class: CS362
Assignment: Assignment 3
Description: Unit test for Minion card
NOTE: code adapted from provided examples
*******************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

// +1 action. Either +2 copper or discard hand and get +4 cards and other players
// with at least 5 cards discard hand and draw 4 cards.

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


// main function for testing Minion card
int main() {
	
	printf("\n********** Testing Minion Card **********\n\n");
	int seed = 1000;
    int numPlayer = 3;
    int thisPlayer = 0, secondPlayer = 1, thirdPlayer = 2;
    int handPos = 0, choice1 = 1, choice2 = 0, choice3 = 0, bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

   
    // ******************* test for choice 1 *****************************
    printf("**********  Choice 1 **********\n\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    // initialize other player's hand due to bug in intializeGame
    G.hand[secondPlayer][0] = copper;
	G.hand[secondPlayer][1] = copper;
	G.hand[secondPlayer][2] = copper;
	G.hand[secondPlayer][3] = estate;
	G.hand[secondPlayer][4] = estate;
	G.handCount[secondPlayer] = 5;

	G.hand[thirdPlayer][0] = copper;
	G.hand[thirdPlayer][1] = copper;
	G.hand[thirdPlayer][2] = copper;
	G.hand[thirdPlayer][3] = estate;
	G.handCount[thirdPlayer] = 4;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call card effect with choice 1
	cardEffect(minion, choice1, choice2, choice3, &testG, handPos, &bonus);

	// test number of new cards
	// note: expect -1 new cards after drawing 0 and discarding village
	printf("New cards: %d, Expected: %d ", testG.handCount[thisPlayer] - G.handCount[thisPlayer], -1);
	compareInt(testG.handCount[thisPlayer] - G.handCount[thisPlayer], -1);

	// test number of actions
	printf("Actions: %d, Expected: %d ", testG.numActions, G.numActions + 1);
	compareInt(testG.numActions, G.numActions + 1);

	// test number of buys
	printf("Buys: %d, Expected: %d ", testG.numBuys, G.numBuys);
	compareInt(testG.numBuys, G.numBuys);

	// test number of coins
	printf("Coins: %d, Expected: %d ", testG.coins, G.coins + 2);
	compareInt(testG.coins, G.coins + 2);

	// test that second player's deck count is unchanged
	printf("Second player's deckCount: %d, Expected: %d ", testG.deckCount[secondPlayer], G.deckCount[secondPlayer]);
	compareInt(testG.deckCount[secondPlayer], G.deckCount[secondPlayer]);

	// test that third player's deck count is unchanged
	printf("Third player's deckCount: %d, Expected: %d ", testG.deckCount[thirdPlayer], G.deckCount[thirdPlayer]);
	compareInt(testG.deckCount[thirdPlayer], G.deckCount[thirdPlayer]);

	// test that second player's cards are unchanged
	printf("Second player's cards: ");
	int i;
	for (i = 0; i < testG.handCount[secondPlayer]; i++) {
		printf("%d ", testG.hand[secondPlayer][i]);
	}
	printf("Expected: ");
	for (i = 0; i < G.handCount[secondPlayer]; i++) {
		printf("%d ", G.hand[secondPlayer][i]);
	}
	int match = 1;
	for (i = 0; i < G.handCount[secondPlayer]; i++) {
		if (G.hand[secondPlayer][i] != testG.hand[secondPlayer][i]) {
			match = 0;
		}
	}
	if (match == 1) {
		printf("***** PASS *****\n");
	}
	else {
		printf("***** FAIL *****\n");
	}

	// test that third player's cards are unchanged
	printf("Third player's cards: ");
	for (i = 0; i < testG.handCount[thirdPlayer]; i++) {
		printf("%d ", testG.hand[thirdPlayer][i]);
	}
	printf("Expected: ");
	for (i = 0; i < G.handCount[thirdPlayer]; i++) {
		printf("%d ", G.hand[thirdPlayer][i]);
	}
	match = 1;
	for (i = 0; i < G.handCount[thirdPlayer]; i++) {
		if (G.hand[thirdPlayer][i] != testG.hand[thirdPlayer][i]) {
			match = 0;
		}
	}
	if (match == 1) {
		printf("***** PASS *****\n");
	}
	else {
		printf("***** FAIL *****\n");
	}

	// ******************* test for choice 1 *****************************
	printf("\n\n**********  Choice 2 **********\n\n");

	seed = 1001;
    numPlayer = 3;

	// initialize second call
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    // initialize other player's hand due to bug in intializeGame
    G.hand[secondPlayer][0] = copper;
	G.hand[secondPlayer][1] = copper;
	G.hand[secondPlayer][2] = copper;
	G.hand[secondPlayer][3] = estate;
	G.hand[secondPlayer][4] = estate;
	G.handCount[secondPlayer] = 5;

	G.hand[thirdPlayer][0] = copper;
	G.hand[thirdPlayer][1] = copper;
	G.hand[thirdPlayer][2] = copper;
	G.hand[thirdPlayer][3] = estate;
	G.handCount[thirdPlayer] = 4;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 0;
	choice2 = 1;

	// call card effect with choice 1
	cardEffect(minion, choice1, choice2, choice3, &testG, handPos, &bonus);

	// test number of new cards
	// note: expect 4 new cards after discarding hand and drawing 4
	printf("New cards: %d, Expected: %d ", testG.handCount[thisPlayer], 4);
	compareInt(testG.handCount[thisPlayer], 4);

	// test for discarded cards
	printf("Discarded: %d, Expected: %d ", testG.discardCount[thisPlayer], 5);
	compareInt(testG.discardCount[thisPlayer], 5);

	// test number of new cards for second player
	printf("New cards: %d, Expected: %d ", testG.handCount[secondPlayer], 4);
	compareInt(testG.handCount[secondPlayer], 4);

	// test for discarded cards for second player
	printf("Discarded: %d, Expected: %d ", testG.discardCount[secondPlayer], 5);
	compareInt(testG.discardCount[secondPlayer], 5);

	// test number of new cards for third player
	// note: expect 0 new cards due to too few cards to discard
	printf("New cards: %d, Expected: %d ", testG.handCount[thirdPlayer] - G.handCount[thirdPlayer], 0);
	compareInt(testG.handCount[thirdPlayer] - G.handCount[thirdPlayer], 0);

	// test for discarded cards for third player
	printf("Discarded: %d, Expected: %d ", testG.discardCount[thirdPlayer], 0);
	compareInt(testG.discardCount[thirdPlayer], 0);	


	printf("\n********** Done Testing Minion Card **********\n\n");

}








