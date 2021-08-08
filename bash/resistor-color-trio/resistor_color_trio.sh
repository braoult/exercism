#!/usr/bin/env bash
#
# V1: initial version
# V2: merged power tables, add index one, improved unit str calculation

# set to mask to enable logs. 0: none, 255: all
((debug=2#00000000))
#((debug=2#00011111))
# $1: log level (mask), then strings to display.
debug () {
    (( debug & $1 )) && shift && echo Line ${BASH_LINENO[0]}: "${@}" >&2
}

die () {
    echo "${@}" >&2
    exit 1
}

usage() {
    die "usage: resistor_color_trio.sh color1 [color2 [color3]]"
}

# not sure here if 1 or 2 colors only should be accepted (not in test cases).
# I will assume yes, it looks more coherent, even if out of scope:
#   "resistor_color_trio.sh Black" will return 0
#   "resistor_color_trio.sh yellow violet" will return 47
# also: (not in test cases), no args will return an error.
#       (in test case), extra colors are ignored, I don't like it, personally
(( $# == 0 )) && usage

# value/power of different colors
declare -A colors=([black]=0 [brown]=1 [red]=2 [orange]=3 [yellow]=4
                   [green]=5 [blue]=6 [violet]=7 [grey]=8 [white]=9)

# available multiplicators (powers of 10).
declare -a powers=([9]=giga [6]=mega [3]=kilo)
idx=("${!powers[@]}")                             # keys copy for reverse loop

params=( ${@,,} )                                 # converting to lower case

(( result=0 ))                                    # final number to display

# I would have preferred to throw an error if $# > 3, instead of ignoring
# extra args...
for ((i=0; i<3 && i<${#params[@]}; ++i)); do
    color="${params[$i]}"                         # color name
    val="${colors[$color]}"                       # color value

    [[ -z "$val" ]] && die "$color: invalid color."
    case $i in
        0)  (( result=val ))
            debug 2 "new color 1 $color/$val. result=$result"
            ;;
        # probably case 0 and 1 could be merged. Easier to read for me
        # by separating them.
        1)  (( result*=10 ))
            (( result+=val ))
            debug 2 "new color 2 $color/$val. result=$result"
            ;;
        2)  (( result *= 10 ** val ))
            debug 2 "new color 3 $color/$val. result=$result"
            ;;
    esac
done

# we have final number, scaling to corresponding strings.
scalestr=""                                       # "giga", etc...

if (( result )); then
    for (( i = ${#idx[@]} - 1; i >= 0; i-- )); do # reverse loop by value
        j=${idx[$i]}                              # also actual power (9, 6, 3)
        (( power = 10 ** $j ))                    # actual value
        debug 8 $i $j ${powers[$j]} $power $result
        if ! (( result % power )); then           # found power
            scalestr=${powers[$j]}
            (( result /= power ))
            break
        fi
    done
fi

echo "$result ${scalestr}ohms"

exit 0

# emacs/vim settings below.
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 50
# fill-column: 80
# End:
# vim: set tabstop=4 expandtab:
