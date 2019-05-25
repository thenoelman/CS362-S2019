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
	printf("Test 1: Test that the player has drawn 2 treasure cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	int beforeAdventurerHandCount = testG.handCount[thisPlayer];
	printf("before adventurer- handCount = %d\n", beforeAdventurerHandCount);

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
	//assert(testG.handCount[thisPlayer] == (G.handCount[thisPlayer] + 2));

	printf("\n");

	/*Test 2  */
	printf("Test 2: cards should come from his own pile.\n");

	printf("before adventurer- deckCount = %d\n", G.deckCount[thisPlayer]);

	printf("after adventurer- deckCount = %d\n", testG.deckCount[thisPlayer]);

	printf("before adventurer- handCount = %d\n", G.handCount[thisPlayer]);

	printf("after adventurer- handCount = %d\n", testG.handCount[thisPlayer]);


	if ((G.deckCount[thisPlayer] - 2) == testG.deckCount[thisPlayer] && 
		(G.handCount[thisPlayer] + 2) == testG.handCount[thisPlayer])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - cards in deck and hand do not add up\n");
		testFailed++;
	}
	/*assert((G.deckCount[thisPlayer] - 2) == testG.deckCount[thisPlayer] &&
		(G.handCount[thisPlayer] + 2) == testG.handCount[thisPlayer]);*/

	printf("\n");

	/*Test 3  */
	printf("Test 3: the 2 new treasure cards are in the player's hand\n");

	int i;
	int coppersBefore = 0;
	int coppersAfter = 0;
	int silversBefore = 0;
	int silversAfter = 0;
	int goldsBefore = 0;
	int goldsAfter = 0;

	for (i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		//printf("hand, this player, before, card %d = %d\n", i, G.hand[thisPlayer][i]);
		//printf("hand, this player, after, card %d = %d\n", i, testG.hand[thisPlayer][i]);
		
		if (G.hand[thisPlayer][i] == 4)
		{
			coppersBefore++;
		}
		else if (G.hand[thisPlayer][i] == 5)
		{
			silversBefore++;
		}
		else if (G.hand[thisPlayer][i] == 6)
		{
			goldsBefore++;
		}

		if (testG.hand[thisPlayer][i] == 4)
		{
			coppersAfter++;
		}
		else if (testG.hand[thisPlayer][i] == 5)
		{
			silversAfter++;
		}
		else if (testG.hand[thisPlayer][i] == 6)
		{
			goldsAfter++;
		}
	}

	printf("coppersBefore = %d\n", coppersBefore);
	int totalCoinsBefore = coppersBefore + silversBefore + goldsBefore;
	int totalCoinsAfter = coppersAfter + silversAfter + goldsAfter;
	printf("coppersAfter = %d\n", coppersAfter);

	printf("totalCoinsBefore = %d\n", totalCoinsBefore);
	printf("totalCoinsAfter = %d\n", totalCoinsAfter);

	if ((totalCoinsBefore + 2 ) == totalCoinsAfter)
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - cards in deck do not add up\n");
		testFailed++;
	}

	//assert(totalCoinsBefore + 2 == totalCoinsAfter);
	printf("\n");

	/*Test 4  */
	printf("Test 4: the other cards have been discarded\n");

	printf("before adventurer- discardCount = %d\n", G.discardCount[thisPlayer]);

	printf("after adventurer- discardCount = %d\n", testG.discardCount[thisPlayer]);

	if (G.discardCount[thisPlayer] <= testG.discardCount[thisPlayer])
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
	/*End of cardtest2 */
	printf("***** Summary results for: %s, %s *****\n", TESTNAME, CARDNAME);
	printf("***** %d Test(s) Passed *****\n", testPassed);
	printf("***** %d Test(s) Failed *****\n", testFailed);
	printf("***** End of %s for %s *****\n\n", TESTNAME, CARDNAME);

	return 0;
}