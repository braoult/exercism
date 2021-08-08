#!/usr/bin/env bash

# set to 0 to disable log function output, 1 otherwise
debug=0

# echoes $1, then exit 1
die ()  {
    echo "$1"
    exit 1
}

# log function takes 1 argument which is echoed if $debug is > 0
# todo: Ad another argument (mask?) to selectively log portions of code
log () {
    (( $debug )) && echo "$1"
}

# check basic errors
(( $# != 2 )) && die "Usage: hamming.sh <string1> <string2>"
(( ${#1} != ${#2} )) && die "left and right strands must be of equal length"

# compare strings
declare -i cur hamming=0

for (( cur=0; cur < ${#1}; cur++ )); do
    log "$cur ${1:$cur:1} ${2:$cur:1}"
    c1="${1:$cur:1}"
    c2="${2:$cur:1}"
    [[ "$c1" != "$c2" ]] && ((hamming++))
    log "hamming in loop=$hamming"
done

echo "$hamming"
exit 0

# Indent style for emacs
# Local Variables:
# sh-basic-offset: 4
# sh-indentation: 4
# indent-tabs-mode: nil
# comment-column: 60
# End:
