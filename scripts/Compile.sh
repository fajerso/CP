#!/usr/bin/bash

file=$1

echo -e "[TUAN DEBUG]" &&
g++ -DTUAN_DEBUG -Wall -Wextra -pedantic -Wshadow -fmax-errors=3 -O2 -std=c++17 $file.cpp -o $file
