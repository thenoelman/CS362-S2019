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
}