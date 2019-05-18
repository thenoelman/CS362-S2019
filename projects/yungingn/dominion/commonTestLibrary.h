#ifndef _COMMONTESTLIBRARY_H
#define _COMMONTESTLIBRARY_H

void noStateChangeTest(int *testPassed, int *testFailed, struct gameState G, struct gameState testG,
	int thisPlayer);

void noStateChangeVictoryKingdomTest(int *testPassed, int *testFailed, struct gameState G, struct gameState testG,
	int thisPlayer);

#endif