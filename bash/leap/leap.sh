#!/usr/bin/env bash

[[ $# != 1 || ! $1 =~ ^[0-9]+$  ]] && echo "Usage: $0 <year>" && exit 1

year=$1
leap=false
if ! (($year % 4)) && (($year % 100))  || !  (($year % 400))
then
    leap=true
fi
echo $leap

exit 0
