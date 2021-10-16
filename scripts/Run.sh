#!/usr/bin/bash

file=$1

echo -e "Output:" &&
echo -e "------------" &&
./$file < in &&
echo -e "------------"
