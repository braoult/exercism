#!/usr/bin/env bash

[[ $# == 0 ]] && echo "" && exit 0

first="$1"
prev="$first"
shift
while [[ $# > 0 ]]; do
    cur="$1"
    echo "For want of a $prev the $cur was lost."
    prev=$cur
    shift
done
echo "And all for the want of a $first."
exit 0
