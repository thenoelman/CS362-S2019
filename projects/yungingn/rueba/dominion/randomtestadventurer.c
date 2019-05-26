#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTNAME "randomtestadventurer"
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

	printf("***** Test results for: %s*****\n", TESTNAME);
	printf("***** Test card: %s *****\n\n", CARDNAME);

	//beginning
	int numberOfRandomTests;
	srand(time(NULL));
	numberOfRandomTests = (rand() % 50) + 1;

	printf("number of random tests executed: %d\n", numberOfRandomTests);

	int j;
	for (j = 0; j < numberOfRandomTests; j++)
	{
		//test drawCard with random decks
		printf("Seed the Adventurer with random decks prior to playing the Adventurer\n");

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
		cardEffect(adventurer, -1, -1, -1, &testG, 0, 0);

		printf("\n");

		printf("this player- discardCount before = %d\n", G.discardCount[thisPlayer]);

		int newDiscardSize;
		newDiscardSize = (rand() % (MAX_DECK - newDeckSize - 1)) + 1;

		printf("Seeding a discard pile with %d random cards\n", newDiscardSize);
		G.discardCount[thisPlayer] = newDiscardSize;

		for (i = 0; i < G.discardCount[thisPlayer]; i++)
		{
			int newRandomCard;
			newRandomCard = (rand() % 26) + 1;
			printf("%d. new random card is %d\n", i, newRandomCard);

			G.discard[thisPlayer][i] = newRandomCard;
		}

		/*Test 1  */
		printf("Test 1: Test that the player has drawn 2 treasure cards\n");

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

		if ((totalCoinsBefore + 2) == totalCoinsAfter)
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
	}

	printf("\n");

	/*End of randomtestadventurer */
	printf("***** Summary results for: %s, %s *****\n", TESTNAME, CARDNAME);
	printf("***** %d Test(s) Passed *****\n", testPassed);
	printf("***** %d Test(s) Failed *****\n", testFailed);
	printf("***** End of %s for %s *****\n\n", TESTNAME, CARDNAME);

	return 0;
}