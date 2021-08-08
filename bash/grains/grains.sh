#!/usr/bin/env bash
#
# V1: initial version
#
# Note: untested on 32 bits and big-endian architectures

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
    die "Error: invalid input"
}

# we want 1 arg only, "total" or digits only.
(($# !=1 )) || \
    [[ "$1" != +([[:digit:]]) ]] && \
    [[ "$1" != "total" ]] && usage

arg="${1##+(0)}"                        # we strip leading zeroes if any
debug 1 arg="$arg"

case "$arg" in
    total)
        # formula to calculate a geometric series of common ratio r and first
        # term f, that is: S=f + fr² + fr³ ... + frⁿ
        # is: S = f * [ (1 - rⁿ⁺¹) / (1 - r) ]
        #
        # for r=2 and f=1, it becomes:
        # S = 1 * (1 - 2ⁿ⁺¹) / -1 = 2ⁿ⁺¹ - 1
        # So here, as total does not accept an argument, such as "last square",
        # the value is 2⁶⁴-1.
        # Notes: (2**64) is 0 on 64 bits, but better not to use this property.
        #        We could also directly output the value, as it is a constant.
        printf -v result "%llu" $(( 2**64 - 1 ))
        ;;
    *)                                  # always digits here
        debug 2 "digits=args"
        (( arg < 1 || arg > 64 )) && usage
        printf -v result "%llu" $(( 2**(arg-1) ))
        ;;
esac

echo "$result"

exit 0

# emacs/vim settings.
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 40
# fill-column: 80
# End:
# vim: set tabstop=4 expandtab:
