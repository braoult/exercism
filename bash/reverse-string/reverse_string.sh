#!/usr/bin/env bash

[[ $# != 1 ]] && echo "usage: $0 string" && exit 1


str=$1
len=${#str}
rev=""

for (( i=0; i<len; ++i ))
do
    rev="${str:i:1}$rev"
done
echo "$rev"
