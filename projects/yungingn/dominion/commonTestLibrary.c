#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

void noStateChangeTest(int *testPassed, int *testFailed, struct gameState G, struct gameState testG,
	int thisPlayer)
{
	printf("Test 3a: Test handCount matches\n");
	printf("other player- handCount before = %d\n", testG.handCount[thisPlayer + 1]);
	printf("other player- handCount after = %d\n", G.handCount[thisPlayer + 1]);
	//assert(testG.handCount[thisPlayer + 1] == G.handCount[thisPlayer + 1]);
	if (testG.handCount[thisPlayer + 1] == G.handCount[thisPlayer + 1])
	{
		printf("+++++ TEST PASSED\n");
		testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - other player's handCount does not match\n");
		*testFailed++;
	}
	printf("\n");

	printf("Test 3b: Test deckCount matches\n");
	printf("other player- deckCount before = %d\n", testG.deckCount[thisPlayer + 1]);
	printf("other player- deckCount after = %d\n", G.deckCount[thisPlayer + 1]);
	assert(testG.deckCount[thisPlayer + 1] == G.deckCount[thisPlayer + 1]);
	if (testG.deckCount[thisPlayer + 1] == G.deckCount[thisPlayer + 1])
	{
		printf("+++++ TEST PASSED\n");
		*testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - other player's deckCount does not match\n");
		*testFailed++;
	}
	printf("\n");

	int i;

	printf("Test 3c: Test that the cards match\n");
	for (i = 0; i < G.deckCount[thisPlayer] - 1; i++)
	{
		printf("deck, this player, before, card %d = %d\n", i, G.deck[thisPlayer][i]);
		printf("deck, this player, after, card %d = %d\n", i, testG.deck[thisPlayer][i]);
		//assert(G.deck[thisPlayer][i] == testG.deck[thisPlayer][i]);

		if (G.deck[thisPlayer][i] == testG.deck[thisPlayer][i])
		{
			printf("+++++ TEST PASSED\n");
			*testPassed++;
		}
		else
		{
			printf("----- TEST FAILED - other player's card does not match\n");
			*testFailed++;
		}
	}
	printf("\n");

	printf("Test 3d: Test that discardCount matches\n");
	printf("other player- discardCount before = %d\n", testG.discardCount[thisPlayer + 1]);
	printf("other player- discardCount after = %d\n", G.discardCount[thisPlayer + 1]);
	//assert(testG.discardCount[thisPlayer + 1] == G.discardCount[thisPlayer + 1]);
	if (testG.discardCount[thisPlayer + 1] == G.discardCount[thisPlayer + 1])
	{
		printf("+++++ TEST PASSED\n");
		*testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - other player's discardCount does not match\n");
		*testFailed++;
	}
	printf("\n");

	printf("Test 3e: Test that discarded cards match\n");
	if (G.discardCount[thisPlayer] == 0)
	{
		printf("There are no discarded cards to test.\n");
	}
	for (i = 0; i < G.discardCount[thisPlayer] - 1; i++)
	{
		printf("discard, other player, before, card %d = %d\n", i, G.discard[thisPlayer][i]);
		printf("discard, other player, after, card %d = %d\n", i, testG.discard[thisPlayer][i]);
		//assert(G.discard[thisPlayer][i] == testG.discard[thisPlayer][i]);

		if (G.discard[thisPlayer][i] == testG.discard[thisPlayer][i])
		{
			printf("+++++ TEST PASSED\n");
			*testPassed++;
		}
		else
		{
			printf("----- TEST FAILED - other player's discarded cards do not match\n");
			*testFailed++;
		}
	}
	printf("\n");

	printf("Test 3f: Test that playedCards matches\n");
	printf("other player- playedCards before = %d\n", testG.playedCards[thisPlayer + 1]);
	printf("other player- playedCards after = %d\n", G.playedCards[thisPlayer + 1]);
	//assert(testG.playedCards[thisPlayer + 1] == G.playedCards[thisPlayer + 1]);
	if (testG.playedCards[thisPlayer + 1] == G.playedCards[thisPlayer + 1])
	{
		printf("+++++ TEST PASSED\n");
		*testPassed++;
	}
	else
	{
		printf("----- TEST FAILED - other player's playedCards does not match\n");
		*testFailed++;
	}
	printf("\n");
}