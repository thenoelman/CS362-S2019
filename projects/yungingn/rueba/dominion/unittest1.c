#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTNAME "unittest1"

void printheaders()
{
	printf("Noel Yunginger\n");
	printf("cs362\n");
	printf("HW3\n\n");

}

int main() {
	int seed = 1000;
	int numPlayers = 2;
	int testPassed = 0;
	int testFailed = 0;
	struct gameState G, testG;

	int k[10] = { smithy, adventurer, village, gardens, great_hall, steward,
			council_room, sea_hag, baron, minion };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printheaders();

	printf("Test results for: %s\n\n", TESTNAME);

	printf("Testing to see if the supplyCount decreases by one after a purchase\n");

	printf("before purchase- supplyCount estate = %d\n", G.supplyCount[estate]);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	buyCard(estate, &testG);//test buying an estate

	printf("after purchase- supplyCount estate = %d\n", testG.supplyCount[estate]);

	if ((G.supplyCount[estate] -1) == testG.supplyCount[estate])
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
	/*End of unittest1 */
	printf("***** Summary results for: %s, *****\n", TESTNAME);
	printf("***** %d Test(s) Passed *****\n", testPassed);
	printf("***** %d Test(s) Failed *****\n", testFailed);
	printf("***** End of %s *****\n\n", TESTNAME);

    return 0;
}
