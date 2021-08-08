#!/usr/bin/env bash

# set to mask to enable logs. 0: none, 255: all
# (( debug=2#00001111 ))
(( debug=2#00000000 ))

# $1: log level (mask), then strings to display.
debug () {
    (( debug & "$1" )) && shift && echo "${@}" >&2
}

usage () {
    echo "usage: ./pangram.sh <string> [...]" >&2
    exit 1
}

# basic args checks: at least 1 arg
(( $# )) || usage

# We will accept mutiple args here: "a" "b" is equivalent to "ab".
# get args in one string, change it to lower case.
IFS=""                                                      # not really needed
string="${*,,}"
debug 1 "string=$string"

# empty string
if (( ! ${#string} )); then
    debug 2 "empty string"
    result=false
else
    result=true

    # loop on all characters, from a to z. We need to check each one.
    for c in {a..z} ; do
        [[ ! ${string} =~ "$c" ]] && result=false && break
    done
fi

echo "$result"
exit 0

# emacs/vim settings.
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 60
# fill-column: 80
# End:
# vim: set tabstop=4 expandtab:
