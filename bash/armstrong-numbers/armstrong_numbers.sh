#!/usr/bin/env bash

# set to mask to enable logs. 0: none, 255: all
(( DEBUG=2#00000000 ))

# $1: log level (mask), then strings to display.
debug () {
    (( DEBUG & $1 )) && shift && echo "${@}" >&2
}

usage () {
    echo "usage: ./armstrong_numbers.sh <number>" >&2
    exit 1
}

# basic args checks: 1 arg, digits  (at least 1) only
(( $# != 1)) || [[ ! "$1" =~ ^[[:digit:]]+$ ]] && usage

number="$1"
digits=${#number}
armstrong=0
result="false"

debug 1 d=$digits n=$number

# armstrong number calculation
for (( i=0; i<digits; ++i )); do
    ((armstrong += ${number:$i:1} ** digits ))
done

debug 2 "armstrong=$armstrong"

((number == armstrong)) && result="true"

echo "$result"

exit 0

# Indent style for emacs
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 60
# End:
