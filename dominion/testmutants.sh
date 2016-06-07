#!/bin/bash

# Change these two variables to match your purposes. The first is your mutant
# directory and the second is the filename scheme your mutants use.
MUT_DIR=/Users/christianmello/Code/cs362sp16_melloc/dominion/mutants/dominionc
MUT_FILE_SCHEME=mutant*_dominion.c

# change this variable to whatever make target you're using.
MAKE_CHOICE=testdominion

cp dominion.c dominion.c.bak

NUM_MUTANTS=$(ls -l $MUT_DIR/$MUT_FILE_SCHEME | grep -v ^l | wc -l | tr -d ' ')

echo "BUILDING $NUM_MUTANTS MUTANTS"

for i in $(ls $MUT_DIR/$MUT_FILE_SCHEME); do
  cp $i dominion.c
done
