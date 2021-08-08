#!/bin/bash

function usage() {
    echo "Usage: ./raindrop.sh number"
    exit 1
}

shopt -s extglob

(( $# == 1 )) || usage
number="$1"
[[ "$number" == +([0-9]) ]] || usage

output=""
(( $number % 3 )) || output+="Pling"
(( $number % 5 )) || output+="Plang"
(( $number % 7 )) || output+="Plong"

echo ${output:-$number}
exit 0
