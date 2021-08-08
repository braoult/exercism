#!/usr/bin/env bash
#
# external tools: none (only integer operations).
#
# V1   : Initial version.
# V2   : Using reference instead of subshell, as of
#         https://stackoverflow.com/questions/540298
#        moved valid numbers in parseval function.
# V3/4 : added some quotes following suggestions

# set to mask to enable logs. 0: none, 255: all
#((DEBUG=2#00001111))
((DEBUG=2#00000000))

# $1: log level (mask), then strings to display.
debug () {
    (( DEBUG & $1 )) && shift && echo "${@}" >&2
}

usage () {
    echo "usage: darts x y" >&2
    exit 1
}

shopt -s extglob

# To be able to use bash only, all numbers will be miltiplied by 1,000.
# Could be higher if we want more precision.
#
# So: 0.1 will be 100, 1 will be 1,000, 10 will br 10000, etc...

# circles. as we will use Pythagoras' theorem, so square value calc here
outer=$((  (10 * 1000 ) ** 2 ))
middle=$(( ( 5 * 1000 ) ** 2 ))
inner=$((  ( 1 * 1000 ) ** 2 ))

debug 1 outer=$outer middle=$middle inner=$inner

# basic args check: 2 args, and decimal numbers, which are:
# optional +- sign, optional digits, optional . and optional digits
(( ${#} != 2 )) && usage

parseval() {
    # integer and decimal parts, final value by ref
    local int dec
    local -n calc=$1

    # check for valid decimal number
    [[ ${2} != ?([-+])+([0-9])?(.*([0-9])) ]] && usage

    IFS=. read int dec <<< "$2"
    debug 2 ${int} ${dec}

    # we accept up to 3 decimals: add 3 zeroes to dec, then keep 3 first digits
    # So a decimal part of "1" will become 100, 01 will become 10, etc...
    # we also take care of leadings 0 (octal notation), and remove leading "-".
    dec="$dec"000
    dec="10#"${dec:0:3}
    int="10#"${int#-}

    debug 2 mult ${int} ${dec}
    calc=$(( (int*1000 + dec) ** 2 ))
}

parseval x "$1"
parseval y "$2"
total=$(( x+y ))
debug 1 x=$x y=$y x+y=$total

(( total <= inner  )) && echo 10 && exit 0
(( total <= middle )) && echo 5 && exit 0
(( total <= outer  )) && echo 1 && exit 0
echo 0 && exit 0

# emacs/vim settings.
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 60
# fill-column: 80
# End:
# vim: set tabstop=4 expandtab:
