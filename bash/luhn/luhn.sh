#!/usr/bin/env bash
#
# External tools: none.
#
# V1: initial version

# set to mask to enable logs. 0: none, 255: all
(( debug=2#00000000 ))
#(( debug=2#00001111 ))
# $1: log level (mask), then strings to display.
debug () {
    (( debug & $1 )) && shift && echo Line ${BASH_LINENO[0]}: "${@}" >&2
}

shopt -s extglob

# basic args usage. We will accept the args to be splitted (out of scope
# for exercise): "luhn.sh '0 0'" is considered equivalent to "luhn.sh 0 0"
IFS="" number="${*// /}"                # merge args, remove all <spaces>
debug 1 number="${number}"

((${#number} < 2)) ||                   # args check: only [0-9], at least 2
    [[ "$number" != +([0-9]) ]] &&
    echo false && exit 0

((len=${#number}))
((sum=0))                               # final sum

for ((i=1; i<=len; ++i)); do            # we loop on each digit, from end
    digit=${number:((-i)):1}
    case $((i % 2)) in
        0)                              # even position (relative to end)
            ((digit *= 2))
            ((digit >= 10)) && ((digit-=9))
            debug 3 even ${digit}
            ;;
        1)                              # odd position (relative to end)
            debug 3 odd ${digit}
            ;;

    esac

    ((sum+=digit))
    debug 2 sum=${sum}
done
((sum % 10)) && echo false || echo true

exit 0

# emacs/vim settings.
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 40
# fill-column: 80
# End:
# vim: set tabstop=4 expandtab:
