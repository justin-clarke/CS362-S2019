/* ****************************************************
Name: Justin Clarke
Date: 5/5/19
Class: CS362
Assignment: Assignment 3
Description: Unit test for Village card
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

// main function for testing Village card
int main() {
	
	printf("\n********** Testing Village Card **********\n\n");
	int seed = 1000;
    int numPlayer = 2;
    int thisPlayer = 0, secondPlayer = 1;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    // initialize second player's hand due to bug in intializeGame
    G.hand[secondPlayer][0] = copper;
	G.hand[secondPlayer][1] = copper;
	G.hand[secondPlayer][2] = copper;
	G.hand[secondPlayer][3] = estate;
	G.hand[secondPlayer][4] = estate;
	G.handCount[secondPlayer] = 5;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call card effect
	cardEffect(village, choice1, choice2, choice3, &testG, handPos, &bonus);

	// test number of new cards
	// note: expect 0 new cards after drawing 1 and discarding village
	printf("New cards: %d, Expected: %d ", testG.handCount[thisPlayer] - G.handCount[thisPlayer], 0);
	compareInt(testG.handCount[thisPlayer] - G.handCount[thisPlayer], 0);

	// test that new cards came from current player's deck
	printf("New deckCount: %d, Expected: %d ", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);
	compareInt(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);

	// test number of actions
	printf("Actions: %d, Expected: %d ", testG.numActions, G.numActions + 2);
	compareInt(testG.numActions, G.numActions + 2);

	// test number of buys
	printf("Buys: %d, Expected: %d ", testG.numBuys, G.numBuys);
	compareInt(testG.numBuys, G.numBuys);

	// test that second player's deck count is unchanged
	printf("second player's deckCount: %d, Expected: %d ", testG.deckCount[secondPlayer], G.deckCount[secondPlayer]);
	compareInt(testG.deckCount[secondPlayer], G.deckCount[secondPlayer]);

	// test that second player's cards are unchanged
	printf("second player's cards: ");
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

	// test that supply of victory cards are unchanged
	int expectedVictoryCount = supplyCount(estate, &G) + supplyCount(duchy, &G) + supplyCount(province, &G);
	int victoryCount = supplyCount(estate, &testG) + supplyCount(duchy, &testG) + supplyCount(province, &testG);
	printf("Victory cards: %d, Expected: %d", victoryCount, expectedVictoryCount);
	compareInt(victoryCount, expectedVictoryCount);


	// test the the supply of kingdom cards are unchanged
	int expectedKingdomCount = supplyCount(adventurer, &G) + supplyCount(council_room, &G) +
							   supplyCount(feast, &G) + supplyCount(gardens, &G) +
							   supplyCount(mine, &G) + supplyCount(remodel, &G) +
							   supplyCount(smithy, &G) + supplyCount(village, &G) +
							   supplyCount(baron, &G) + supplyCount(great_hall, &G);
	int kingdomCount = supplyCount(adventurer, &testG) + supplyCount(council_room, &testG) +
							   supplyCount(feast, &testG) + supplyCount(gardens, &testG) +
							   supplyCount(mine, &testG) + supplyCount(remodel, &testG) +
							   supplyCount(smithy, &testG) + supplyCount(village, &testG) +
							   supplyCount(baron, &testG) + supplyCount(great_hall, &testG);
	
	printf("Kingdom card count: %d, Expected: %d", kingdomCount, expectedKingdomCount);
	compareInt(kingdomCount, expectedKingdomCount);


	printf("\n********** Done Testing Council Room Card **********\n\n");

}



