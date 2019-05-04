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

	printheaders();

	printf("Test results for: %s\n\n", TESTNAME);

    return 0;
}
