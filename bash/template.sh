#!/usr/bin/env bash
#
# External tools: none.
#
# V1: initial version

shopt -s extglob

# set to mask to enable logs. 0: none, 255: all
(( debug=2#00000000 ))
# (( debug=2#00001111 ))
# $1: log level (mask), then strings to display.
debug () {
    (( debug & $1 )) && shift && echo Line ${BASH_LINENO[0]}: "${@}" >&2
    #local -i i
    #if (( debug & $1 )) ; then
    #    for ((i=1; i<$1; ++i)); do
    #        echo -n " "
    #    done
    #    shift
    #    echo "${BASH_LINENO[0]}: ${@}" >&2
    #fi

}

die () {
    echo "${@}" >&2
    exit 1
}
usage() {
    die "usage: resistor_color_trio.sh color1 [color2 [color3]]"
}

exit 0

# emacs/vim settings.
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 40
# fill-column: 80
# End:
# vim: set tabstop=4 expandtab:
