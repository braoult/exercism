#!/usr/bin/env bash
#
# V1: initial version

shopt -s extglob

# set to mask to enable logs. 0: none, 255: all
(( debug=2#00000000 ))
(( debug=2#00001111 ))
# $1: log level (mask), then strings to display.
debug () {
    (( debug & $1 )) && shift && echo Line ${BASH_LINENO[0]}: "${@}" >&2
}

die () {
    echo "${@}" >&2
    exit 1
}
usage() {
    die "usage: bowling.sh r1-20 [r21 [r22]]"
}
# pincount > 10. $1: frame
highroll() {
    die Frame "Frame $1: Pin count exceeds pins on the lane."
}
# pincount > 10. $1: frame
negativeroll() {
    die Frame "Frame $1: Negative roll is invalid."
}


# args test: 10 rolls mandatory
#(($# < 20)) && usage
rolls=($@)
debug 1 rolls=${rolls[@]}

((score = 0))                                     # total score
((tempscore = 0))                                 # tmp score (for spare/strike)

declare -a frames                                 # frames scores
declare -a opened                                 # spare:2, strike:1

((frame=-1))                                       # current frame

((curroll=1))                                     # roll in frame: 1:1st, 2:2nd
((i=0))
for ((roll=0; roll<$#; ++roll)); do
    debug 2 loop roll="$roll"

    (( ! roll % 2 && frame++ ))
    exit 0
    (( score=${rolls[$i]} ))
    #(( score < 0 )) && || score > 10)) && echo 1
    #if ((!roll % 2)); then                        # first roll in frame


    ((framescore=0))                              # current frame score


    for j in 0 1; do
        (( roll = ${rolls[$i]} ))
        ((roll < 0)) && die Frame $((curframe+1)): Negative roll is invalid.
        (( framescore += roll ))
        ((framescore == 10)) && ((opened[$curframe] = j+1))
        (( i++ ))
    done
    debug 2 curframe=$curframe score=$framescore

    #if ((roll))

    ((framescore > 10)) && wrongroll $curframe $curroll $framescore

    frame[$curframe]=$framescore


    ((curroll = -curroll))
done

# emacs/vim settings.
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 50
# fill-column: 80
# End:
# vim: set tabstop=4 expandtab:
