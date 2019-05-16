/* ****************************************************
Name: Justin Clarke
Date: 5/5/19
Class: CS362
Assignment: Assignment 3
Description: Card test for Great Hall card
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


// main function for testing Adventurer card
int main() {
	
	printf("\n********** Testing Salvager Card **********\n\n");
	int seed = 1000;
    int numPlayer = 2;
    int thisPlayer = 0, otherPlayer = 1;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, salvager, great_hall};
    struct gameState G, testG;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    // initialize other player's hand due to bug in intializeGame
    G.hand[otherPlayer][0] = copper;
	G.hand[otherPlayer][1] = copper;
	G.hand[otherPlayer][2] = copper;
	G.hand[otherPlayer][3] = copper;
	G.hand[otherPlayer][4] = great_hall;
	G.handCount[otherPlayer] = 5;

    // copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call card effect
	choice1 = 1;
	cardEffect(salvager, choice1, choice2, choice3, &testG, handPos, &bonus);

	// test number of new cards
	// note: expect -2 new cards after trashing 1 card and discarding salvager
	printf("New cards: %d, Expected: %d ", testG.handCount[thisPlayer] - G.handCount[thisPlayer],  -2);
	compareInt(testG.handCount[thisPlayer] - G.handCount[thisPlayer],  -2);

	// test number of actions
	printf("Actions: %d, Expected: %d ", testG.numActions, G.numActions);
	compareInt(testG.numActions, G.numActions);

	// test number of buys
	printf("Buys: %d, Expected: %d ", testG.numBuys, G.numBuys + 1);
	compareInt(testG.numBuys, G.numBuys + 1);

	// test coins received
	printf("Coins: %d, Expected: %d ", testG.coins, G.coins + getCost(handCard(choice1, &testG)));
	compareInt(testG.coins, G.coins + getCost(handCard(choice1, &testG)));

	// reset game state
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 0;  // no card is trashed
	cardEffect(salvager, choice1, choice2, choice3, &testG, handPos, &bonus);

	// test coins received
	printf("Coins: %d, Expected: %d ", testG.coins, G.coins);
	compareInt(testG.coins, G.coins);

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

	// test that other player's cards are unchanged
	printf("Other player's cards: ");
	int i;
	for (i = 0; i < testG.handCount[otherPlayer]; i++) {
		printf("%d ", testG.hand[otherPlayer][i]);
	}
	printf("Expected: ");
	for (i = 0; i < G.handCount[otherPlayer]; i++) {
		printf("%d ", G.hand[otherPlayer][i]);
	}
	int match = 1;
	for (i = 0; i < G.handCount[otherPlayer]; i++) {
		if (G.hand[otherPlayer][i] != testG.hand[otherPlayer][i]) {
			match = 0;
		}
	}
	if (match == 1) {
		printf("***** PASS *****\n");
	}
	else {
		printf("***** FAIL *****\n");
	}

	printf("\n********** Done Testing Salvager Card **********\n\n");


}





