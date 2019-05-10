CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.o testme.c
	gcc -o testme testme.c -g testme.o $(CFLAGS)

all: testme

clean: 
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out