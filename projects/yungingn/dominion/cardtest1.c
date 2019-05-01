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
	int xtraCoins = 0;
	int shuffledCards = 0;

	int i, j, m;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int remove1, remove2;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
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
	choice1 = 1;
	printf("before smithy- hand count = %d\n", testG.handCount[thisPlayer]);
	cardEffect_smithy(thisPlayer, &testG, handpos);
	printf("after smithy and discard hand count = %d\n", testG.handCount[thisPlayer]);
	printf("expected = %d\n", G.handCount[thisPlayer] + newCards - discarded);

	printf("\n");
	/*Test 2  */
	printf("Test 2: 3 cards should come from his own pile.\n");

	printf("\n");
	/*Test 3  */
	printf("Test 3: No state change should occur for other players.\n");

	printf("\n");
	/*Test 4  */
	printf("Test 4: No state change should occur to the victory card piles and kingdom card piles.\n");

	/*End of cardtest1 */
	printf("***** End of %s for %s *****\n\n", TESTNAME, CARDNAME);

	return 0;
}