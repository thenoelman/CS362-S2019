#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTNAME "unittest1"

void printheaders()
{
	printf("Noel Yunginger\n");
	printf("cs362\n");
	printf("HW3\n\n");

}

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

	printheaders();

	printf("Test results for: %s\n\n", TESTNAME);

	printf("\n");
	/*End of unittest1 */
	printf("***** Summary results for: %s, *****\n", TESTNAME);
	printf("***** %d Test(s) Passed *****\n", testPassed);
	printf("***** %d Test(s) Failed *****\n", testFailed);
	printf("***** End of %s *****\n\n", TESTNAME);

    return 0;
}
