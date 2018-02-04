CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

test1: dominion.o unittest1.c
	gcc -o test1 unittest1.c -g  dominion.o rngs.o $(CFLAGS)

test2: dominion.o unittest2.c
	gcc -o test2 unittest2.c -g  dominion.o rngs.o $(CFLAGS)

test3: dominion.o unittest3.c
	gcc -o test3 unittest3.c -g  dominion.o rngs.o $(CFLAGS)

test4: dominion.o unittest4.c
	gcc -o test4 unittest4.c -g  dominion.o rngs.o $(CFLAGS)

ctest1: dominion.o cardtest1.c
	gcc -o ctest1 cardtest1.c -g  dominion.o rngs.o $(CFLAGS)

ctest2: dominion.o cardtest2.c
	gcc -o ctest2 cardtest2.c -g  dominion.o rngs.o $(CFLAGS)

ctest3: dominion.o cardtest3.c
	gcc -o ctest3 cardtest3.c -g  dominion.o rngs.o $(CFLAGS)

ctest4: dominion.o cardtest4.c
	gcc -o ctest4 cardtest4.c -g  dominion.o rngs.o $(CFLAGS)

student: dominion.o testUpdateCoins.c
	gcc -o student testUpdateCoins.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe test1 test2 test3 test4 ctest1 ctest2 ctest3 ctest4 playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
