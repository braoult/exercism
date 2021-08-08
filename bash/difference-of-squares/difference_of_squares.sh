#!/usr/bin/env bash
#
# External tools: none.
# subshell: none.
#
# V1: initial version

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
    die "usage: difference_of_squares.sh command color"
}

debug 1 "#=$#" "arg=$1"
(($# != 2)) || [[ $1 != @(square_of_sum|sum_of_squares|difference) ]] || \
    [[ "$2" != +([[:digit:]]) ]] && usage

# the 2 next functions will set $1 to the calculated value for $2
sum_of_squares () {                     # set $1 to sum of squares ($2)
    local -n res=$1
    local val=$2

    # the sum of 1st n integers squares is:
    #  S = 1² + 2² + 3² ..... + (n-1)² + n²
    #    = [ n * (n+1) * (2n+1) ] / 6
    # demonstration on:
    #   http://www.takayaiwamoto.com/Sums_and_Series/sumsqr_1.html
    (( res = val * (val+1) * (2*val + 1) / 6 ))
    debug 2 "sum_of_squares($val) = $res"
}
square_of_sum () {                      # set $1 to square of sum ($2)
    local -n res=$1
    local val=$2

    # The sum of n 1st integers is:
    #  S  = 1 + 2 + 3 ... + (n-1) + n
    #     = [ n * (n+1) ] / 2
    # demonstration is trivial for this one.
    (( res = (val * (val+1) / 2 ) ** 2 ))
    debug 2 "square_of_sum($val) = $res"
}

action="$1"
(( num = $2 ))

case "$action" in
     square_of_sum)
         square_of_sum result "$num"
         debug 3 "result after calling square_of_sum: $result"
         ;;
     sum_of_squares)
         sum_of_squares result "$num"
         debug 3 "result after calling sum_of_squares: $result"
         ;;
     difference)
         square_of_sum SqSum "$num"
         sum_of_squares SumSq "$num"
         ((result = SqSum - SumSq))
         debug 3 "result after calling difference: $result"
esac

echo $result
exit 0

# emacs/vim settings.
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 40
# fill-column: 80
# End:
# vim: set tabstop=4 expandtab:
