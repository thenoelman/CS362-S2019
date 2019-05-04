#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTNAME "cardtest1"
#define CARDNAME "smithy"

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

	printf("***** Test results for: %s *****\n", TESTNAME);
	printf("***** Test card: %s *****\n\n", CARDNAME);

	/*Test 1  */
	printf("Test 1: Current player should receive exactly 3 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	int beforeSmithyHandCount = testG.handCount[thisPlayer];
	printf("before smithy- handCount = %d\n", beforeSmithyHandCount);
	int deckCountBeforeSmithy = testG.deckCount[thisPlayer];
	
	//play the smithy
	cardEffect_smithy(thisPlayer, &testG, handpos);

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
	assert(testG.handCount[thisPlayer] != (G.handCount[thisPlayer] + newCards - discarded));

	printf("\n");

	/*Test 2  */
	printf("Test 2: 3 cards should come from his own pile.\n");

	printf("before smithy- deckCount = %d\n", deckCountBeforeSmithy);

	printf("after smithy- deckCount = %d\n", testG.deckCount[thisPlayer]);
	assert(deckCountBeforeSmithy != testG.deckCount[thisPlayer]);

	int drawnCards = testG.handCount[thisPlayer] + discarded - beforeSmithyHandCount;
	printf("drawnCards = %d\n", drawnCards);

	if((deckCountBeforeSmithy - drawnCards) == testG.deckCount[thisPlayer])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - cards in deck do not add up\n");
		testFailed++;
	}
	assert((deckCountBeforeSmithy - drawnCards) == testG.deckCount[thisPlayer]);

	printf("\n");
	/*Test 3  */
	printf("Test 3: No state change should occur for other players.\n\n");

	printf("Test 3a: Test handCount matches\n");
	printf("other player- handCount before = %d\n", testG.handCount[thisPlayer + 1]);
	printf("other player- handCount after = %d\n", G.handCount[thisPlayer + 1]);
	assert(testG.handCount[thisPlayer + 1] == G.handCount[thisPlayer + 1]);
	if (testG.handCount[thisPlayer + 1] == G.handCount[thisPlayer + 1])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - other player's handCount does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 3b: Test deckCount matches\n");
	printf("other player- deckCount before = %d\n", testG.deckCount[thisPlayer + 1]);
	printf("other player- deckCount after = %d\n", G.deckCount[thisPlayer + 1]);
	assert(testG.deckCount[thisPlayer + 1] == G.deckCount[thisPlayer + 1]);
	if (testG.deckCount[thisPlayer + 1] == G.deckCount[thisPlayer + 1])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - other player's deckCount does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 3c: Test that the cards match\n");
	for (int i = 0; i < G.deckCount[thisPlayer] - 1; i++)
	{
		printf("deck, other player, before, card %d = %d\n", i, G.deck[thisPlayer][i]);
		printf("deck, other player, after, card %d = %d\n", i, testG.deck[thisPlayer][i]);
		assert(G.deck[thisPlayer][i] == testG.deck[thisPlayer][i]);

		if (G.deck[thisPlayer][i] == testG.deck[thisPlayer][i])
		{
			printf("+++++ TEST PASSED\n");
			testPassed++;
		}
		else
		{
			printf("----- TEST FAILED - other player's card does not match\n");
			testFailed++;
		}
	}
	printf("\n");

	printf("Test 3d: Test that discardCount matches\n");
	printf("other player- discardCount before = %d\n", testG.discardCount[thisPlayer + 1]);
	printf("other player- discardCount after = %d\n", G.discardCount[thisPlayer + 1]);
	assert(testG.discardCount[thisPlayer + 1] == G.discardCount[thisPlayer + 1]);
	if (testG.discardCount[thisPlayer + 1] == G.discardCount[thisPlayer + 1])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - other player's discardCount does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 3e: Test that discarded cards match\n");
	if (G.discardCount[thisPlayer] == 0)
	{
		printf("There are no discarded cards to test.\n");
	}
	for (int i = 0; i < G.discardCount[thisPlayer] - 1; i++)
	{
		printf("discard, other player, before, card %d = %d\n", i, G.discard[thisPlayer][i]);
		printf("discard, other player, after, card %d = %d\n", i, testG.discard[thisPlayer][i]);
		assert(G.discard[thisPlayer][i] == testG.discard[thisPlayer][i]);

		if (G.discard[thisPlayer][i] == testG.discard[thisPlayer][i])
		{
			printf("+++++ TEST PASSED\n");
			testPassed++;
		}
		else
		{
			printf("----- TEST FAILED - other player's discarded cards do not match\n");
			testFailed++;
		}
	}
	printf("\n");

	printf("Test 3f: Test that playedCards matches\n");
	printf("other player- playedCards before = %d\n", testG.playedCards[thisPlayer + 1]);
	printf("other player- playedCards after = %d\n", G.playedCards[thisPlayer + 1]);
	assert(testG.playedCards[thisPlayer + 1] == G.playedCards[thisPlayer + 1]);
	if (testG.playedCards[thisPlayer + 1] == G.playedCards[thisPlayer + 1])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - other player's playedCards does not match\n");
		testFailed++;
	}
	printf("\n");

	/*Test 4  */
	printf("Test 4: No state change should occur to the victory card piles and kingdom card piles.\n");

	printf("\n");
	printf("Test 4a: Test that the supply count of curse matches\n");
	printf("supply count before: curse= %d\n", testG.supplyCount[0]);
	printf("supply count after: curse= %d\n", G.supplyCount[0]);
	assert(testG.supplyCount[0] == G.supplyCount[0]);
	if (testG.supplyCount[0] == G.supplyCount[0])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of curse does not match\n");
		testFailed++;
	}
	printf("\n");


	/*End of cardtest1 */
	printf("***** Summary results for: %s, %s *****\n", TESTNAME, CARDNAME);
	printf("***** %d Test(s) Passed *****\n", testPassed);
	printf("***** %d Test(s) Failed *****\n", testFailed);
	printf("***** End of %s for %s *****\n\n", TESTNAME, CARDNAME);

	return 0;
}

