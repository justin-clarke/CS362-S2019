/* ****************************************************
Name: Justin Clarke
Date: 5/19/19
Class: CS362
Assignment: Assignment 4
Description: Random test for Smithy card
NOTE: code adapted from provided examples
*******************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


// function to compare 2 integers for test result and expected value
int compareInt(int a, int b) {
	if (a == b) {
		printf("***** PASS *****\n");
		return 1;
	}
	else {
		printf("***** FAIL *****\n");
		return 0;
	}	
}


// main function for testing Adventurer card
int main() {
	
	printf("\n********** Testing Smithy Card **********\n\n");
	int seed = 1000;
    int numPlayer = (rand() % (4 - 2 + 1) + 2);
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    int count = 0;
    int failCount = 0;
    while (count < 20) {

    	printf("\n\n***** Round %d *****\n\n", count);

	    memset(&G, 23, sizeof(struct gameState));   // clear the game state
	    initializeGame(numPlayer, k, seed, &G); // initialize a new game

	    int handPos = rand() % 5;
	    G.hand[0][handPos] = smithy;

	    // initialize other player's hands
	    int i, j;
	    for (i = 1; i < numPlayer; i++) {
	    	int numCards = (rand() % (8 - 5 + 1)) + 5;
	    	for (j = 0; j < numCards; j++) {
	    		G.hand[i][j] = rand() % 26;
	    	}
	    	G.handCount[i] = numCards;

	    	int numDeck = rand() % 11;
	    	for (j = 0; j < numDeck; j++) {
	    		G.deck[i][j] = rand() % 26;
	    	}
	    }

	    // copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		// call card function
		refactoredSmithy(0, &testG, handPos);


		// test deck count
		printf("Deck count: %d, Expected %d ", testG.deckCount[0], G.deckCount[0] - 3);
		if (compareInt(testG.deckCount[0], G.deckCount[0] - 3) == 0) {
			failCount += 1;
		}

		// test number of actions
		printf("Actions: %d, Expected: %d ", testG.numActions, G.numActions);
		if (compareInt(testG.numActions, G.numActions) == 0) {
			failCount += 1;
		}

		// test number of buys
		printf("Buys: %d, Expected: %d ", testG.numBuys, G.numBuys);
		if (compareInt(testG.numBuys, G.numBuys) == 0) {
			failCount += 1;
		}

		// test number of coins
		printf("Coins: %d, Expected: %d ", testG.coins, G.coins);
		if (compareInt(testG.coins, G.coins) == 0) {
			failCount += 1;
		}

		// test discard count:
		printf("Played card count: %d, Expected: %d ", testG.playedCardCount, G.playedCardCount + 1);
		if (compareInt(testG.playedCardCount, G.playedCardCount + 1) == 0) {
			failCount += 1;
		}

		// test number of new cards
		// note: expect 2 new cards after drawing 3 and discarding smithy
		printf("New cards: %d, Expected: %d ", testG.handCount[0] - G.handCount[0], 2);
		if (compareInt(testG.handCount[0] - G.handCount[0], 2) == 0) {
			failCount += 1;
		}

		// test that new cards came from current player's deck
		printf("New deckCount: %d, Expected: %d ", testG.deckCount[0], G.deckCount[0] - 3);
		if (compareInt(testG.deckCount[0], G.deckCount[0] - 3) == 0) {
			failCount += 1;
		}
		
		// test that other player's deck counts are unchanged
		for (i = 1; i < numPlayer; i++) {
			printf("Player %d's deckCount: %d, Expected: %d ", i, testG.deckCount[i], G.deckCount[i]);
			if (compareInt(testG.deckCount[i], G.deckCount[i]) == 0) {
				failCount += 1;
			}
		}

		// test that supply of victory cards are unchanged
		int expectedVictoryCount = supplyCount(estate, &G) + supplyCount(duchy, &G) + supplyCount(province, &G);
		int victoryCount = supplyCount(estate, &testG) + supplyCount(duchy, &testG) + supplyCount(province, &testG);
		printf("Victory cards: %d, Expected: %d ", victoryCount, expectedVictoryCount);
		if (compareInt(victoryCount, expectedVictoryCount) == 0) {
			failCount += 1;
		}

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
		if (compareInt(kingdomCount, expectedKingdomCount) == 0) {
			failCount += 1;
		}

		count += 1;

	}
	
	printf("\n**********  Tests Complete! There were %d failures  **********\n\n", failCount);

	return 0;
}


















