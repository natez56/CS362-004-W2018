CFLAGS = -Wall -fpic -coverage -lm
TESTPROJ = unittest1 unittest2 unittest3 unittest4 randomtestcard1
TESTPROJ += cardtest1 cardtest2 cardtest3 cardtest4
TESTPROJ += randomtestcard1 randomtestcard2 randomtestadventurer

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

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 unittest1.c -g  dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	echo "dominion.c test coverage:" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "isGameOver() dominion.c function coverage:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/isGameOver/{n;p; n;p; n;p; n;p}' >> unittestresults.out

	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 unittest2.c -g  dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	echo "dominion.c global coverage:" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "discardCard() dominion.c function coverage:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/discardCard/{n;p; n;p; n;p; n;p}' >> unittestresults.out

	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 unittest3.c -g  dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	echo "dominion.c global coverage:" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "fullDeckCount() dominion.c function coverage:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/fullDeckCount/{n;p; n;p; n;p; n;p}' >> unittestresults.out

	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 unittest4.c -g  dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	echo "dominion.c global coverage:" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "gainCard() dominion.c function coverage:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/gainCard/{n;p; n;p; n;p; n;p}' >> unittestresults.out

	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c -g  dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	echo "dominion.c global coverage:" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "playSmithy() dominion.c function coverage:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/playSmithy/{n;p; n;p; n;p; n;p}' >> unittestresults.out

	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c -g  dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	echo "dominion.c global coverage:" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "playAdventurer() dominion.c function coverage:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/playAdventurer/{n;p; n;p; n;p; n;p}' >> unittestresults.out

	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c -g  dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	echo "dominion.c global coverage:" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "playVillage() dominion.c function coverage:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/playVillage/{n;p; n;p; n;p; n;p}' >> unittestresults.out

	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c -g  dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	echo "dominion.c global coverage:" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "playMine() dominion.c function coverage:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/playMine/{n;p; n;p; n;p; n;p}' >> unittestresults.out

	echo "Final dominion.c global coverage results:"
	gcov dominion.c >> unittestresults.out

randomtestcard1.out: dominion.o randomtestcard1.c
	echo "randomtestcard1.c:" >> randomtestcard1.out
	gcc -o randomtestcard1 randomtestcard1.c -g  dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	echo "\ndominion.c global coverage:" >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	echo "playSmithy() dominion.c function coverage:" >> randomtestcard1.out
	gcov -abcfu dominion.c | sed -n '/playSmithy/{n;p; n;p; n;p; n;p}' >> randomtestcard1.out

randomtestcard2.out: dominion.o randomtestcard2.c
	echo "randomtestcard2.c:" >> randomtestcard2.out
	gcc -o randomtestcard2 randomtestcard2.c -g  dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	echo "\ndominion.c global coverage:" >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	echo "playVillage() dominion.c function coverage:" >> randomtestcard2.out
	gcov -abcfu dominion.c | sed -n '/playVillage/{n;p; n;p; n;p; n;p}' >> randomtestcard2.out

randomtestadventurer.out: dominion.o randomtestadventurer.c
	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtestadventurer randomtestadventurer.c -g  dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	echo "\ndominion.c global coverage:" >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	echo "playAdventurer() dominion.c function coverage:" >> randomtestadventurer.out
	gcov -abcfu dominion.c | sed -n '/playAdventurer/{n;p; n;p; n;p; n;p}' >> randomtestadventurer.out

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

unittest1: dominion.o unittest1.c
	gcc -o unittest1 unittest1.c -g  dominion.o rngs.o $(CFLAGS)

unittest2: dominion.o unittest2.c
	gcc -o unittest2 unittest2.c -g  dominion.o rngs.o $(CFLAGS)

unittest3: dominion.o unittest3.c
	gcc -o unittest3 unittest3.c -g  dominion.o rngs.o $(CFLAGS)

unittest4: dominion.o unittest4.c
	gcc -o unittest4 unittest4.c -g  dominion.o rngs.o $(CFLAGS)

cardtest1: dominion.o cardtest1.c
	gcc -o cardtest1 cardtest1.c -g  dominion.o rngs.o $(CFLAGS)

cardtest2: dominion.o cardtest2.c
	gcc -o cardtest2 cardtest2.c -g  dominion.o rngs.o $(CFLAGS)

cardtest3: dominion.o cardtest3.c
	gcc -o cardtest3 cardtest3.c -g  dominion.o rngs.o $(CFLAGS)

cardtest4: dominion.o cardtest4.c
	gcc -o cardtest4 cardtest4.c -g  dominion.o rngs.o $(CFLAGS)

randomtestcard1: dominion.o randomtestcard1.c
	gcc -o randomtestcard1 randomtestcard1.c -g  dominion.o rngs.o $(CFLAGS)

randomtestcard2: dominion.o randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c -g  dominion.o rngs.o $(CFLAGS)

randomtestadventurer: dominion.o randomtestadventurer.c
	gcc -o randomtestadventurer randomtestadventurer.c -g  dominion.o rngs.o $(CFLAGS)

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
	rm -f *.o playdom.exe $(TESTPROJ) playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
