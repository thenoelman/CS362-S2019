CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)


#########

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


unittestresults: cardtest1.c dominion.o rngs.o
	gcc commonTestLibrary.c -c
	gcc -o cardtest1 cardtest1.c -g  dominion.o rngs.o commonTestLibrary.o $(CFLAGS)
	gcc -o cardtest2 cardtest2.c -g  dominion.o rngs.o commonTestLibrary.o $(CFLAGS)
	gcc -o cardtest3 cardtest3.c -g  dominion.o rngs.o commonTestLibrary.o $(CFLAGS)
	gcc -o cardtest4 cardtest4.c -g  dominion.o rngs.o commonTestLibrary.o $(CFLAGS)
	gcc -o cardtest5 cardtest5.c -g  dominion.o rngs.o commonTestLibrary.o $(CFLAGS)
	gcc -o unittest1 unittest1.c -g  dominion.o rngs.o commonTestLibrary.o $(CFLAGS)
	gcc -o unittest2 unittest2.c -g  dominion.o rngs.o commonTestLibrary.o $(CFLAGS)
	gcc -o unittest3 unittest3.c -g  dominion.o rngs.o commonTestLibrary.o $(CFLAGS)
	gcc -o unittest4 unittest4.c -g  dominion.o rngs.o commonTestLibrary.o $(CFLAGS)
	gcc -o randomtestcard1 randomtestcard1.c -g  dominion.o rngs.o commonTestLibrary.o $(CFLAGS)
	gcc -o randomtestcard2 randomtestcard2.c -g  dominion.o rngs.o commonTestLibrary.o $(CFLAGS)
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o commonTestLibrary.o $(CFLAGS)

	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	./cardtest5 >> unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out

	echo "" >> unittestresults.out
	echo "gcov results" >> unittestresults.out
	echo "" >> unittestresults.out

	./randomtestcard1 >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	./randomtestadventurer >> randomtestresults.out
	echo "" >> randomtestresults.out

	echo "Gcov Results" >> randomtestresults.out
	gcov dominion.c -b >> randomtestresults.out
	gcov dominion.c >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittestresults.out
	rm -f cardtest1 cardtest2 cardtest3 cardtest4 cardtest5 unittest1 unittest2 unittest3 unittest4 
	rm -f randomtestadventurer randomtestcard1 randomtestcard2
