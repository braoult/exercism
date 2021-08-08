#!/usr/bin/env bash

#str=$1

# the next two lines would trim leading & trailing blank chars. I believe the exercise
# should be amended to avoid "One for  , one for me."
#str="${str#"${str%%[![:space:]]*}"}"   # remove leading blanks
#str="${str%"${str##*[![:space:]]}"}"   # remove trailing blanks

#[[ ${#str} = 0 ]] && str="you"

echo "One for ${1:-you}, one for me."
