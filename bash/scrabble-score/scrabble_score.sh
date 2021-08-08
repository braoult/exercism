#!/usr/bin/env bash
#
# V1: initial version
# V2: check for alphabetic chars only

shopt -s extglob

# set to mask to enable logs. 0: none, 255: all
(( debug=2#00000000 ))
#(( debug=2#00001111 ))
# $1: log level (mask), then strings to display.
debug () {
    (( debug & $1 )) && shift && echo Line ${BASH_LINENO[0]}: "${@}" >&2
}

die () {
    echo "${@}" >&2
    exit 1
}
usage() {
    die "usage: scrabble_score.sh word"
}

declare -A values=(
    [A]=1 [E]=1 [I]=1 [O]=1 [U]=1 [L]=1 [N]=1 [R]=1 [S]=1 [T]=1
    [D]=2 [G]=2
    [B]=3 [C]=3 [M]=3 [P]=3
    [F]=4 [H]=4 [V]=4 [W]=4 [Y]=4
    [K]=5
    [J]=8 [X]=8
    [Q]=10 [Z]=10
)

(($# != 1)) && usage
word="${1^^}"                                     # capitalize
[[ "$word" != +([[:upper:]]) ]] && usage          # accept only alpha chars

debug 1 arg="$word"
((score=0))

for (( i=0; i<${#word}; ++i )); do
    c="${word:$i:1}"
    ((score += ${values[$c]}))
done

echo "$score"
exit 0

# emacs/vim settings.
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 50
# fill-column: 80
# End:
# vim: set tabstop=4 expandtab:
