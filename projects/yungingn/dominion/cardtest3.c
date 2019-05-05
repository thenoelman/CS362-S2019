#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "commonTestLibrary.h"

#define TESTNAME "cardtest3"
#define CARDNAME "village"

int main() {
	int newCards = 3;
	int discarded = 1;

	int handpos = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int testPassed = 0;
	int testFailed = 0;
	int cardDrawn;
	int z = 0;// this is the counter for the temp hand

	struct gameState G, testG;

	int k[10] = { smithy, adventurer, village, gardens, great_hall, steward,
			council_room, sea_hag, baron, minion };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("***** Test results for: %s *****\n", TESTNAME);
	printf("***** Test card: %s *****\n\n", CARDNAME);

	/*Test 1  */
	printf("Test 1: Test that the player has drawn 1 card\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	int beforeVillageHandCount = G.handCount[thisPlayer];
	printf("before village- handCount = %d\n", beforeVillageHandCount);
	int deckCountBeforeVillage = G.deckCount[thisPlayer];

	cardEffect(village, -1, -1, -1, &testG, 0, 0);

	printf("after village = %d\n", testG.handCount[thisPlayer]);

	printf("expected = %d\n", G.handCount[thisPlayer] + 2);
	if (testG.handCount[thisPlayer] != (G.handCount[thisPlayer] + 2))
	{
		printf("----- TEST FAILED - only 1 new card should be in handCount\n");
		testFailed++;
	}
	else
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	assert(testG.handCount[thisPlayer] != (G.handCount[thisPlayer] + newCards - discarded));

	printf("\n");

	/*Test 2  */
	printf("Test 2: Test that the player has gained 2 actions\n");

	printf("Number of actions before drawing the village: %d\n", G.numActions);
	printf("Number of actions after drawing the village: %d\n", testG.numActions);
	assert(G.numActions + 2 == testG.numActions);

	if(G.numActions + 2 == testG.numActions)
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
	printf("----- TEST FAILED - drawing a village did not gain 2 actions\n");
	testFailed++;
	}

	/*Test 3  */
	printf("Test 3: No state change should occur for other players\n");

	noStateChangeTest(&testPassed, &testFailed, G, testG, thisPlayer);


	/*Test 4  */
	printf("Test 4: No state change should occur to the victory card piles and kingdom card piles\n");

	printf("\n");
	/*End of cardtest3 */
	printf("***** Summary results for: %s, %s *****\n", TESTNAME, CARDNAME);
	printf("***** %d Test(s) Passed *****\n", testPassed);
	printf("***** %d Test(s) Failed *****\n", testFailed);
	printf("***** End of %s for %s *****\n\n", TESTNAME, CARDNAME);

	return 0;
}