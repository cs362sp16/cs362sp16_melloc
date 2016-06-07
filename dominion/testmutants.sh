#!/bin/bash

MUT_DIR=mutants/compiled
MUT_FILE_SCHEME=mutant*_dominion.c

KILLED_DIR=mutants/killed

# change this variable to whatever make target you're using.
MAKE_CHOICE=testdominion

NUM_MUTANTS=$(ls -l $MUT_DIR/$MUT_FILE_SCHEME | grep -v ^l | wc -l | tr -d ' ')

echo "BUILDING $NUM_MUTANTS MUTANTS"

make -B testdominion > /dev/null 2>&1
./testdominion 42 > testdominionorig.output

mkdir $KILLED_DIR

cp dominion.c dominion.c.bak

for i in $(ls $MUT_DIR/$MUT_FILE_SCHEME); do
  KILL_MUTANT=no

  cp $i dominion.c

  echo Testing $i

  # UNIT TESTS
  make -B unittests > /dev/null 2>&1
  for i in $(ls unittest*.out); do
    ./$i > /dev/null 2>&1
    if [[ $? != 0 ]]; then
      KILL_MUTANT=yes
      echo Fail on unit test!
    fi
  done

  # CARD TESTS
  make -B cardtests > /dev/null 2>&1
  for i in $(ls cardtest*.out); do
    ./$i > /dev/null 2>&1
    if [[ $? != 0 ]]; then
      KILL_MUTANT=yes
      echo Fail on card test!
    fi
  done

  # RANDOM TESTS
  make -B randomtestcards > /dev/null 2>&1
  for i in $(ls randomtest*.out); do
    ./$i > /dev/null 2>&1
    if [[ $? != 0 ]]; then
      KILL_MUTANT=yes
      echo Fail on random test!
    fi
  done

  # TESTDOMINION
  make -B testdominion > /dev/null 2>&1
  ./testdominion 42 > testdominionmutant.output
  diff testdominionorig.output testdominionmutant.output > /dev/null 2>&1
  if [[ $? != 0 ]]; then
    KILL_MUTANT=yes
    echo Fail on testdominion diff!
  fi

  if [[ $KILL_MUTANT == yes ]]; then
    cp $i $KILLED_DIR
    echo $i has been killed!
  fi

done

cp dominion.c.bak dominion.c
