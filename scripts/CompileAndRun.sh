#!/usr/bin/bash

compile_file=$1

echo -e "[TUAN DEBUG]" &&
g++ -DTUAN_DEBUG -Wall -Wextra -pedantic -Wshadow -fmax-errors=2 -O2 -std=c++17 $compile_file.cpp -o $compile_file &&
echo -e "\nOutput:" &&
echo -e "------------" &&
./$compile_file < in &&
echo -e "------------"
