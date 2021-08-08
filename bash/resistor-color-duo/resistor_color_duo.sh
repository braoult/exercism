#!/usr/bin/env bash

usage () {
    if [[ $# == 1 ]]; then
        echo "$1: invalid color."
    else
        echo "usage: resistor_color.sh color1 color2"
    fi
    exit 1
}

declare -A colors
colors=(
    [black]=0
    [brown]=1
    [red]=2
    [orange]=3
    [yellow]=4
    [green]=5
    [blue]=6
    [violet]=7
    [grey]=8
    [white]=9
)
result=""

# not sure here if 1 color only should be accepted (case is not in test). I assume yes:
# "resistor_color.sh Black" will return 0
# also (not in test cases), no args will return an error.
[[ $# == 0 ]] && usage

# we will accept capitalized colors: converting to lower case
for i in ${1,,} ${2,,}
do
    [[ ${colors[$i]} == "" ]] && usage "$i"
    result+=${colors[$i]}
done
echo $result
exit 0
