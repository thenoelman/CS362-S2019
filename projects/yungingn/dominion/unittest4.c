#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTNAME "unittest4"

int main() {
	int newCards = 3;
	int discarded = 1;

	int handpos = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int testPassed = 0;
	int testFailed = 0;
	struct gameState G, testG;

	int k[10] = { smithy, adventurer, village, gardens, great_hall, steward,
			council_room, sea_hag, baron, minion };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("Test results for: %s\n\n", TESTNAME);

	printf("Testing to see if the total cards increases after a purchase of an estate\n");

	printf("before purchase- handCount = %d\n", G.handCount[thisPlayer]);
	printf("before purchase- deckCount = %d\n", G.deckCount[thisPlayer]);
	printf("before purchase- discardCount = %d\n", G.discardCount[thisPlayer]);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	buyCard(estate, &testG);//test buying an estate

	printf("after purchase- handCount = %d\n", testG.handCount[thisPlayer]);
	printf("after purchase- deckCount = %d\n", testG.deckCount[thisPlayer]);
	printf("after purchase- discardCount = %d\n", testG.discardCount[thisPlayer]);

	if ((G.handCount[thisPlayer] + G.deckCount[thisPlayer] + G.discardCount[thisPlayer] + 1)
		== (testG.handCount[thisPlayer] + testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer]))
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - cards in deck do not add up\n");
		testFailed++;
	}

	printf("\n");
	/*End of unittest4 */
	printf("***** Summary results for: %s, *****\n", TESTNAME);
	printf("***** %d Test(s) Passed *****\n", testPassed);
	printf("***** %d Test(s) Failed *****\n", testFailed);
	printf("***** End of %s *****\n\n", TESTNAME);

	return 0;
}
