#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

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
	printf("supply count before: curse= %d\n", testG.supplyCount[curse]);
	printf("supply count after: curse= %d\n", G.supplyCount[curse]);
	assert(testG.supplyCount[curse] == G.supplyCount[curse]);
	if (testG.supplyCount[curse] == G.supplyCount[curse])
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

	printf("Test 4b: Test that the supply count of estate matches\n");
	printf("supply count before: estate= %d\n", testG.supplyCount[estate]);
	printf("supply count after: estate= %d\n", G.supplyCount[estate]);
	assert(testG.supplyCount[estate] == G.supplyCount[estate]);
	if (testG.supplyCount[estate] == G.supplyCount[estate])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of estate does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4c: Test that the supply count of duchy matches\n");
	printf("supply count before: duchy= %d\n", testG.supplyCount[duchy]);
	printf("supply count after: duchy= %d\n", G.supplyCount[duchy]);
	assert(testG.supplyCount[duchy] == G.supplyCount[duchy]);
	if (testG.supplyCount[duchy] == G.supplyCount[duchy])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of duchy does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4d: Test that the supply count of province matches\n");
	printf("supply count before: province= %d\n", testG.supplyCount[province]);
	printf("supply count after: province= %d\n", G.supplyCount[province]);
	assert(testG.supplyCount[province] == G.supplyCount[province]);
	if (testG.supplyCount[province] == G.supplyCount[province])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of province does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4e: Test that the supply count of copper matches\n");
	printf("supply count before: copper= %d\n", testG.supplyCount[copper]);
	printf("supply count after: copper= %d\n", G.supplyCount[copper]);
	assert(testG.supplyCount[copper] == G.supplyCount[copper]);
	if (testG.supplyCount[copper] == G.supplyCount[copper])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of copper does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4f: Test that the supply count of silver matches\n");
	printf("supply count before: silver= %d\n", testG.supplyCount[silver]);
	printf("supply count after: silver= %d\n", G.supplyCount[silver]);
	assert(testG.supplyCount[silver] == G.supplyCount[silver]);
	if (testG.supplyCount[silver] == G.supplyCount[silver])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of silver does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4g: Test that the supply count of gold matches\n");
	printf("supply count before: gold= %d\n", testG.supplyCount[gold]);
	printf("supply count after: gold= %d\n", G.supplyCount[gold]);
	assert(testG.supplyCount[gold] == G.supplyCount[gold]);
	if (testG.supplyCount[gold] == G.supplyCount[gold])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of gold does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4h: Test that the supply count of adventurer matches\n");
	printf("supply count before: adventurer= %d\n", testG.supplyCount[adventurer]);
	printf("supply count after: adventurer= %d\n", G.supplyCount[adventurer]);
	assert(testG.supplyCount[adventurer] == G.supplyCount[adventurer]);
	if (testG.supplyCount[adventurer] == G.supplyCount[adventurer])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of adventurer does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4i: Test that the supply count of council_room matches\n");
	printf("supply count before: council_room= %d\n", testG.supplyCount[council_room]);
	printf("supply count after: council_room= %d\n", G.supplyCount[council_room]);
	assert(testG.supplyCount[council_room] == G.supplyCount[council_room]);
	if (testG.supplyCount[council_room] == G.supplyCount[council_room])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of council_room does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4j: Test that the supply count of feast matches\n");
	printf("supply count before: feast= %d\n", testG.supplyCount[feast]);
	printf("supply count after: feast= %d\n", G.supplyCount[feast]);
	assert(testG.supplyCount[feast] == G.supplyCount[feast]);
	if (testG.supplyCount[feast] == G.supplyCount[feast])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of feast does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4k: Test that the supply count of gardens matches\n");
	printf("supply count before: gardens= %d\n", testG.supplyCount[gardens]);
	printf("supply count after: gardens= %d\n", G.supplyCount[gardens]);
	assert(testG.supplyCount[gardens] == G.supplyCount[gardens]);
	if (testG.supplyCount[gardens] == G.supplyCount[gardens])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of gardens does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4l: Test that the supply count of mine matches\n");
	printf("supply count before: mine= %d\n", testG.supplyCount[mine]);
	printf("supply count after: mine= %d\n", G.supplyCount[mine]);
	assert(testG.supplyCount[mine] == G.supplyCount[mine]);
	if (testG.supplyCount[mine] == G.supplyCount[mine])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of mine does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4m: Test that the supply count of remodel matches\n");
	printf("supply count before: remodel= %d\n", testG.supplyCount[remodel]);
	printf("supply count after: remodel= %d\n", G.supplyCount[remodel]);
	assert(testG.supplyCount[remodel] == G.supplyCount[remodel]);
	if (testG.supplyCount[remodel] == G.supplyCount[remodel])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of remodel does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4n: Test that the supply count of village matches\n");
	printf("supply count before: village= %d\n", testG.supplyCount[village]);
	printf("supply count after: village= %d\n", G.supplyCount[village]);
	assert(testG.supplyCount[village] == G.supplyCount[village]);
	if (testG.supplyCount[village] == G.supplyCount[village])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of village does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4o: Test that the supply count of baron matches\n");
	printf("supply count before: baron= %d\n", testG.supplyCount[baron]);
	printf("supply count after: baron= %d\n", G.supplyCount[baron]);
	assert(testG.supplyCount[baron] == G.supplyCount[baron]);
	if (testG.supplyCount[baron] == G.supplyCount[baron])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of baron does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4p: Test that the supply count of great_hall matches\n");
	printf("supply count before: great_hall= %d\n", testG.supplyCount[great_hall]);
	printf("supply count after: great_hall= %d\n", G.supplyCount[great_hall]);
	assert(testG.supplyCount[great_hall] == G.supplyCount[great_hall]);
	if (testG.supplyCount[great_hall] == G.supplyCount[great_hall])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of great_hall does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4q: Test that the supply count of minion matches\n");
	printf("supply count before: minion= %d\n", testG.supplyCount[minion]);
	printf("supply count after: minion= %d\n", G.supplyCount[minion]);
	assert(testG.supplyCount[minion] == G.supplyCount[minion]);
	if (testG.supplyCount[minion] == G.supplyCount[minion])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of minion does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4r: Test that the supply count of steward matches\n");
	printf("supply count before: steward= %d\n", testG.supplyCount[steward]);
	printf("supply count after: steward= %d\n", G.supplyCount[steward]);
	assert(testG.supplyCount[steward] == G.supplyCount[steward]);
	if (testG.supplyCount[steward] == G.supplyCount[steward])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of steward does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4s: Test that the supply count of tribute matches\n");
	printf("supply count before: tribute= %d\n", testG.supplyCount[tribute]);
	printf("supply count after: tribute= %d\n", G.supplyCount[tribute]);
	assert(testG.supplyCount[tribute] == G.supplyCount[tribute]);
	if (testG.supplyCount[tribute] == G.supplyCount[tribute])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of tribute does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4t: Test that the supply count of ambassador matches\n");
	printf("supply count before: ambassador= %d\n", testG.supplyCount[ambassador]);
	printf("supply count after: ambassador= %d\n", G.supplyCount[ambassador]);
	assert(testG.supplyCount[ambassador] == G.supplyCount[ambassador]);
	if (testG.supplyCount[ambassador] == G.supplyCount[ambassador])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of ambassador does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4u: Test that the supply count of cutpurse matches\n");
	printf("supply count before: cutpurse= %d\n", testG.supplyCount[cutpurse]);
	printf("supply count after: cutpurse= %d\n", G.supplyCount[cutpurse]);
	assert(testG.supplyCount[cutpurse] == G.supplyCount[cutpurse]);
	if (testG.supplyCount[cutpurse] == G.supplyCount[cutpurse])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of cutpurse does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4v: Test that the supply count of embargo matches\n");
	printf("supply count before: embargo= %d\n", testG.supplyCount[embargo]);
	printf("supply count after: embargo= %d\n", G.supplyCount[embargo]);
	assert(testG.supplyCount[embargo] == G.supplyCount[embargo]);
	if (testG.supplyCount[embargo] == G.supplyCount[embargo])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of embargo does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4w: Test that the supply count of outpost matches\n");
	printf("supply count before: outpost= %d\n", testG.supplyCount[outpost]);
	printf("supply count after: outpost= %d\n", G.supplyCount[outpost]);
	assert(testG.supplyCount[outpost] == G.supplyCount[outpost]);
	if (testG.supplyCount[outpost] == G.supplyCount[outpost])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of outpost does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4x: Test that the supply count of salvager matches\n");
	printf("supply count before: salvager= %d\n", testG.supplyCount[salvager]);
	printf("supply count after: salvager= %d\n", G.supplyCount[salvager]);
	assert(testG.supplyCount[salvager] == G.supplyCount[salvager]);
	if (testG.supplyCount[salvager] == G.supplyCount[salvager])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of salvager does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4y: Test that the supply count of sea_hag matches\n");
	printf("supply count before: sea_hag= %d\n", testG.supplyCount[sea_hag]);
	printf("supply count after: sea_hag= %d\n", G.supplyCount[sea_hag]);
	assert(testG.supplyCount[sea_hag] == G.supplyCount[sea_hag]);
	if (testG.supplyCount[sea_hag] == G.supplyCount[sea_hag])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of sea_hag does not match\n");
		testFailed++;
	}
	printf("\n");

	printf("Test 4z: Test that the supply count of treasure_map matches\n");
	printf("supply count before: treasure_map= %d\n", testG.supplyCount[treasure_map]);
	printf("supply count after: treasure_map= %d\n", G.supplyCount[treasure_map]);
	assert(testG.supplyCount[treasure_map] == G.supplyCount[treasure_map]);
	if (testG.supplyCount[treasure_map] == G.supplyCount[treasure_map])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - supply count of treasure_map does not match\n");
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

