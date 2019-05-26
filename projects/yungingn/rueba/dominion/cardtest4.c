#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTNAME "cardtest4"
#define CARDNAME "steward"

int main() {
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
	printf("***** Test card: %s *****\n\n", CARDNAME);

	/*Test 1  */
	printf("Test 1: Test that the player has drawn 2 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("this player- handCount before = %d\n", G.handCount[thisPlayer]);
	printf("this player- deckCount before = %d\n", G.deckCount[thisPlayer]);

	//play the steward
	cardEffect(steward, 1, -1, -1, &testG, 0, 0);

	printf("this player- handCount after (with discard) = %d\n", testG.handCount[thisPlayer]);
	printf("this player- deckCount after  = %d\n", testG.deckCount[thisPlayer]);

	if ((G.handCount[thisPlayer] + 1) == testG.handCount[thisPlayer] 
		)
		
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED \n");
		testFailed++;
	}
	/*assert((G.deckCount[thisPlayer] -1) == testG.deckCount[thisPlayer] &&
		G.handCount[thisPlayer] == testG.handCount[thisPlayer]);*/

	printf("\n");

	/*Test 3  */
	printf("Test 3: No state change should occur for other players\n");

	noStateChangeTest(&testPassed, &testFailed, G, testG, thisPlayer);

	/*Test 4  */
	printf("Test 4: No state change should occur to the victory card piles and kingdom card piles\n");

	noStateChangeVictoryKingdomTest(&testPassed, &testFailed, G, testG, thisPlayer);

	printf("\n");
	/*End of cardtest4 */
	printf("***** Summary results for: %s, %s *****\n", TESTNAME, CARDNAME);
	printf("***** %d Test(s) Passed *****\n", testPassed);
	printf("***** %d Test(s) Failed *****\n", testFailed);
	printf("***** End of %s for %s *****\n\n", TESTNAME, CARDNAME);

	return 0;
}