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

	printf("***** Test results for: %s *****\n", TESTNAME);
	printf("***** Test card: %s *****\n\n", CARDNAME);

	/*Test 1  */
	printf("Test 1: Current player should receive exactly 3 cards\n");

	/*Test 2  */
	printf("Test 2: 3 cards should come from his own pile.\n");

	/*Test 3  */
	printf("Test 3: No state change should occur for other players.\n");

	/*Test 4  */
	printf("Test 4: No state change should occur to the victory card piles and kingdom card piles.\n");

	/*End of cardtest1 */
	printf("***** End of %s for %s *****\n\n", TESTNAME, CARDNAME);

	return 0;
}