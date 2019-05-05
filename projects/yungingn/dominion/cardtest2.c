#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTNAME "cardtest2"
#define CARDNAME "adventurer"

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
	printf("Test 1: Test that the player has drawn 2 treasure cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	int beforeAdventurerHandCount = testG.handCount[thisPlayer];
	printf("before adventurer- handCount = %d\n", beforeAdventurerHandCount);
	int deckCountBeforeAdventurer = testG.deckCount[thisPlayer];

	cardEffect(adventurer, -1, -1, -1, &testG, 0, 0);

	printf("after adventurer and discard hand count = %d\n", testG.handCount[thisPlayer]);

	printf("expected = %d\n", G.handCount[thisPlayer] + 2);
	if (testG.handCount[thisPlayer] != (G.handCount[thisPlayer] + 2))
	{
		printf("----- TEST FAILED - only 2 new cards should be in handCount\n");
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
	printf("Test 2: cards should come from his own pile.\n");

	printf("before adventurer- deckCount = %d\n", deckCountBeforeAdventurer);

	printf("after adventurer- deckCount = %d\n", testG.deckCount[thisPlayer]);
	//assert(deckCountBeforeAdventurer != testG.deckCount[thisPlayer]);

	int drawnCards = testG.handCount[thisPlayer] + discarded - beforeAdventurerHandCount;
	printf("drawnCards = %d\n", drawnCards);

	if ((deckCountBeforeAdventurer - drawnCards) == testG.deckCount[thisPlayer])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - cards in deck do not add up\n");
		testFailed++;
	}
	//assert((deckCountBeforeAdventurer - drawnCards) == testG.deckCount[thisPlayer]);

	printf("\n");

	printf("test: %d\n", G.deckCount[thisPlayer]);
	printf("test2: %d\n", G.handCount[thisPlayer]);

	/*Test 3  */
	printf("Test 3: the 2 new treasure cards are in the player's hand\n");

	for (int i = 0; i < G.deckCount[thisPlayer] - 1; i++)
	{
		printf("card %d = %d\n", i, G.deck[thisPlayer][i]);

	}

	/*Test 4  */
	printf("Test 4: the other cards have been discarded\n");

	printf("\n");
	/*End of cardtest2 */
	printf("***** Summary results for: %s, %s *****\n", TESTNAME, CARDNAME);
	printf("***** %d Test(s) Passed *****\n", testPassed);
	printf("***** %d Test(s) Failed *****\n", testFailed);
	printf("***** End of %s for %s *****\n\n", TESTNAME, CARDNAME);

	return 0;
}