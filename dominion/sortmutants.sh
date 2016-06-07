#!/bin/bash

# Change these two variables to match your purposes. The first is your mutant
# directory and the second is the filename scheme your mutants use.
MUT_DIR=mutants/dominionc
MUT_FILE_SCHEME=mutant*_dominion.c

NON_COMPILED_DIR=mutants/not_compiled
COMPILED_DIR=mutants/compiled

# change this variable to whatever make target you're using.
MAKE_CHOICE=testdominion

mkdir $NON_COMPILED_DIR
mkdir $COMPILED_DIR

cp dominion.c dominion.c.bak

NUM_MUTANTS=$(ls -l $MUT_DIR/$MUT_FILE_SCHEME | grep -v ^l | wc -l | tr -d ' ')

echo "BUILDING $NUM_MUTANTS MUTANTS"

for i in $(ls $MUT_DIR/$MUT_FILE_SCHEME); do
  cp $i dominion.c
  make -B $MAKE_CHOICE > /dev/null 2>&1
  if [[ $? != 0 ]]; then
    cp $i $NON_COMPILED_DIR
    echo $i failed to compile!
  else
    cp $i $COMPILED_DIR
  fi
done

cp dominion.c.bak dominion.c
