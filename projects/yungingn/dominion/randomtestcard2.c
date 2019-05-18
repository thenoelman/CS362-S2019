#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTNAME "randomtestcard2"
#define CARDNAME "village"

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

	printf("***** Test results for: %s*****\n", TESTNAME);
	printf("***** Test card: %s *****\n\n", CARDNAME);

	//beginning
	int numberOfRandomTests;
	numberOfRandomTests = (rand() % 50) + 1;

	printf("number of random tests executed: %d\n", numberOfRandomTests);

	int j;
	for (j = 0; j < numberOfRandomTests; j++)
	{
		//test drawCard with random decks
		printf("Seed the Village with random decks prior to playing the Village\n");

		//randomize the deck
		srand(time(NULL));

		int newDeckSize;
		newDeckSize = (rand() % (MAX_DECK - 6)) + 6;

		printf("Seeding a new deck with %d random cards\n", newDeckSize);
		G.deckCount[thisPlayer] = newDeckSize;

		int i;
		for (i = 0; i < G.deckCount[thisPlayer]; i++)
		{
			int newRandomCard;
			newRandomCard = (rand() % 26) + 1;
			printf("%d. new random card is %d\n", i, newRandomCard);

			G.deck[thisPlayer][i] = newRandomCard;
		}

		printf("this player- handCount before = %d\n", G.handCount[thisPlayer]);
		printf("this player- deckCount before = %d\n", G.deckCount[thisPlayer]);

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		//play the great_hall
		cardEffect(village, -1, -1, -1, &testG, 0, 0);

		printf("\n");
		/*Test 1  */
		printf("Test 1: Test that the player has drawn 1 card\n");

		printf("this player- handCount after = %d\n", testG.handCount[thisPlayer]);
		printf("this player- deckCount after (with discard) = %d\n", testG.deckCount[thisPlayer]);

		if ((G.deckCount[thisPlayer] - 1) == testG.deckCount[thisPlayer] &&
			G.handCount[thisPlayer] == testG.handCount[thisPlayer])//because of discarding
		{
			printf("+++++ TEST PASSED\n");
			testPassed++;
		}
		else
		{
			printf("----- TEST FAILED - only 1 new card should be in handCount\n");
			testFailed++;
		}

		printf("\n");
		/*Test 2  */
		printf("Test 2: Test that the player has gained 2 actions\n");

		printf("Number of actions before drawing the village: %d\n", G.numActions);
		printf("Number of actions after drawing the village: %d\n", testG.numActions);
		assert(G.numActions + 2 == testG.numActions);

		if (G.numActions + 2 == testG.numActions)
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

		noStateChangeVictoryKingdomTest(&testPassed, &testFailed, G, testG, thisPlayer);
	}

	printf("\n");

	/*End of randomtestcard2 */
	printf("***** Summary results for: %s, %s *****\n", TESTNAME, CARDNAME);
	printf("***** %d Test(s) Passed *****\n", testPassed);
	printf("***** %d Test(s) Failed *****\n", testFailed);
	printf("***** End of %s for %s *****\n\n", TESTNAME, CARDNAME);

	return 0;
}

