CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

cardEffects.o: cardEffects.h cardEffects.c
	gcc -c cardEffects.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o cardEffects.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o cardEffects.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o cardEffects.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -rf *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM

myTest:
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest1.c rngs.c cardEffects.c -o unittest1 -lm -g
	./unittest1 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest2.c rngs.c cardEffects.c -o unittest2 -lm -g
	./unittest2 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest3.c rngs.c cardEffects.c -o unittest3 -lm -g
	./unittest3 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest4.c rngs.c cardEffects.c -o unittest4 -lm -g
	./unittest4 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest1.c rngs.c cardEffects.c -o cardtest1 -lm -g
	./cardtest1 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest2.c rngs.c cardEffects.c -o cardtest2 -lm -g
	./cardtest2 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest3.c rngs.c cardEffects.c -o cardtest3 -lm -g
	./cardtest3 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	rm -f dominion.c.gcov dominion.gcda dominion.gcno
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest4.c rngs.c cardEffects.c -o cardtest4 -lm -g
	./cardtest4 1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
