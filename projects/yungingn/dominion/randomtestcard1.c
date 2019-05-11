#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

#define TESTNAME "randomtestcard1"
#define CARDNAME "great_hall"

int main() {
	/*int newCards = 3;
	int discarded = 1;

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

	printf("***** Test results for: %s *****\n", TESTNAME);
	printf("***** Test card: %s *****\n\n", CARDNAME);*/

	/*Test 1  */
	/*printf("Test 1: Current player should receive exactly 3 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	int beforeSmithyHandCount = testG.handCount[thisPlayer];
	printf("before smithy- handCount = %d\n", beforeSmithyHandCount);
	int deckCountBeforeSmithy = testG.deckCount[thisPlayer];

	//play the smithy
	//cardEffect_smithy(thisPlayer, &testG, handpos);
	cardEffect(smithy, -1, -1, -1, &testG, 0, 0);

	printf("after smithy and discard hand count = %d\n", testG.handCount[thisPlayer]);

	printf("expected = %d\n", G.handCount[thisPlayer] + newCards - discarded);
	if (testG.handCount[thisPlayer] != (G.handCount[thisPlayer] + newCards - discarded))
	{
		printf("----- TEST FAILED - 3 cards were not drawn\n");
		testFailed++;
	}
	else
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	assert(testG.handCount[thisPlayer] != (G.handCount[thisPlayer] + newCards - discarded));*/

	printf("\n");

	

	/*End of randomtestcard1 */
	printf("***** Summary results for: %s, %s *****\n", TESTNAME, CARDNAME);
	//printf("***** %d Test(s) Passed *****\n", testPassed);
	//printf("***** %d Test(s) Failed *****\n", testFailed);
	printf("***** End of %s for %s *****\n\n", TESTNAME, CARDNAME);

	return 0;
}

