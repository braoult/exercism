#!/usr/bin/env bash
# V1: initial version
# V2: cosmetic changes

shopt -s extglob

# set to mask to enable logs. 0: none, 255: all
#(( debug=2#00001111 ))
# $1: log level (mask), then strings to display.
debug () {
    (( debug & $1 )) && shift && echo "${@}" >&2
}

arg="$1"

# trim all blank characters safely
arg="${arg//[[:space:]]/}"
debug 1 trim "$arg"

# and check if last char is question mark
[[ ${arg: -1} == "?" ]] && question=+

# the tricky part in test is that non alpha characters are considered
# differently in tests, depending on the rest of the string (having
# letters or not). So we remove them in that case.
[[ "$arg" == *[[:alpha:]]* ]] && arg="${arg//[![:alpha:]]/}"
debug 1 special "$arg" $question

# and now proceed with rules
case "$arg$question" in
    "")
        echo "Fine. Be that way!"
        ;;
    +([[:upper:]])+)
        echo "Calm down, I know what I'm doing!"
        ;;
    *+)
        echo "Sure."
        ;;
    +([[:upper:]]))
        echo "Whoa, chill out!"
        ;;
    *)
        echo "Whatever."
        ;;
esac
exit 0

# emacs/vim settings.
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 50
# fill-column: 80
# End:
# vim: set tabstop=4 expandtab:
