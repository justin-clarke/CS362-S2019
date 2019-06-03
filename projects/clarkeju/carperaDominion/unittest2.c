/* ****************************************************
Name: Justin Clarke
Date: 5/5/19
Class: CS362
Assignment: Assignment 3
Description: Unit test for Council Room card
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


// main function for testing Council Room card
int main() {
	
	printf("\n********** Testing Council Room Card **********\n\n");
	int seed = 1000;
    int numPlayer = 3;
    int thisPlayer = 0, secondPlayer = 1, thirdPlayer = 2;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

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
	G.hand[thirdPlayer][4] = estate;
	G.handCount[thirdPlayer] = 5;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call card effect
	cardEffect(council_room, choice1, choice2, choice3, &testG, handPos, &bonus);

	// test number of new cards
	// note: expect 3 new cards after drawing 4 and discarding council_room
	printf("New cards: %d, Expected: %d ", testG.handCount[thisPlayer] - G.handCount[thisPlayer], 3);
	compareInt(testG.handCount[thisPlayer] - G.handCount[thisPlayer], 3);

	// test that new cards came from current player's deck
	printf("New deckCount: %d, Expected: %d ", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 4);
	compareInt(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 4);

	// test number of actions
	printf("Actions: %d, Expected: %d ", testG.numActions, G.numActions);
	compareInt(testG.numActions, G.numActions);

	// test number of buys
	printf("Buys: %d, Expected: %d ", testG.numBuys, G.numBuys + 1);
	compareInt(testG.numBuys, G.numBuys + 1);

	// test number of new cards for second player
	printf("New cards second player: %d, Expected: %d ", testG.handCount[secondPlayer] - G.handCount[secondPlayer], 1);
	compareInt(testG.handCount[secondPlayer] - G.handCount[secondPlayer], 1);

	// test number of new cards for third player
	printf("New cards third player: %d, Expected: %d ", testG.handCount[thirdPlayer] - G.handCount[thirdPlayer], 1);
	compareInt(testG.handCount[thirdPlayer] - G.handCount[thirdPlayer], 1);	

	// test that new cards came from second player's deck
	printf("Second player deckCount: %d, Expected: %d ", testG.deckCount[secondPlayer], G.deckCount[secondPlayer] - 1);
	compareInt(testG.deckCount[secondPlayer], G.deckCount[secondPlayer] - 1);

	// test that new cards came from third player's deck
	printf("Third player deckCount: %d, Expected: %d ", testG.deckCount[thirdPlayer], G.deckCount[thirdPlayer] - 1);
	compareInt(testG.deckCount[thirdPlayer], G.deckCount[thirdPlayer] - 1);

	// test that supply of victory and kingdom cards are unchanged
	int expectedVictoryCount = supplyCount(estate, &G) + supplyCount(duchy, &G) + supplyCount(province, &G);
	int victoryCount = supplyCount(estate, &testG) + supplyCount(duchy, &testG) + supplyCount(province, &testG);
	printf("Victory cards: %d, Expected: %d ", victoryCount, expectedVictoryCount);
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
	
	printf("Kingdom card count: %d, Expected: %d ", kingdomCount, expectedKingdomCount);
	compareInt(kingdomCount, expectedKingdomCount);



	printf("\n********** Done Testing Council Room Card **********\n\n");

}




