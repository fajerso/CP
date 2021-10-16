#!/usr/bin/bash

DIR_NAME=$1
N=$2

ALPHABET=("A" "B" "C" "D" "E" "F" "G" "H" "I" "J" "K" "L" "M" "N" "O" "P" "Q" "R" "S" "T" "U" "V")

mkdir $DIR_NAME && cd $DIR_NAME &&
for ((i = 0; i < $N; i++))
do  mkdir ${ALPHABET[$i]} && cd ${ALPHABET[$i]} &&
    cp ~/Programming/Library/template.cpp ${ALPHABET[$i]}.cpp &&
    touch in out &&
    cd ..;
done &&
cd ..;
