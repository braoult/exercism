#!/usr/bin/env bash

usage () {
    echo "usage: grep.sh [-nlivx] [-e] pattern file [...]"
    exit 1
}

# no arguments
LN=                                               # be sure variables are reset
FN=
RV=
FL=
MULTI=

# parse args:
while getopts ":nlivxe" arg; do
    case $arg in
        n) LN=t ;;                                # will print line number
        l) FN=t ;;                                # only file names
        i) shopt -s nocasematch ;;                # case insensitive
        v) RV=t ;;                                # reverse search
        x) FL=t ;;                                # full line search
        e) break ;;                               # not in exercise: end args
        *) usage ;;
    esac
done
shift $((OPTIND-1))

# need at least pattern and 1 file.
# TODO: consider stdin if no file
[[ $# < 2 ]] && usage
[[ $# > 2 ]] && MULTI=t

# full line match
if [[ $FL = t ]]; then
    pattern="^$1\$"
else
    pattern=".*$1.*"
fi

shift

# will prevent leading/trailing whitespaces to be trimmed
IFS=""

while [[ $# > 0 ]]; do
    file="$1"
    if [[ ! -r "$file" ]]; then
        echo "$file: no such file, or not readable."
        exit 1
    fi

    lnum=0                                        # line number

    match=n
    while read -r line ; do                        # will consider '\' as normal char
        (( lnum ++ ))

        if [[ $line =~ $pattern ]] ; then         # line match
            match=y

            # print only filename, go to next file
            [[ $FN = t ]] && echo "$file" && break

            # not reverse matching only
            if [[ $RV != t ]]; then
                # multiple files: print filename
                [[ $MULTI == t ]] && echo -n "$file:"
                [[ $LN = t ]] && echo -n "$lnum:"
                echo "$line"
            fi
        else
            # reverse match
            if [[ $RV == t ]]; then
                # print only filename, go to next file
                [[ $FN = t ]] && echo "$file" && break

                # multiple files: print filename
                [[ $MULTI == t ]] && echo -n "$file:"
                [[ $LN = t ]] && echo -n "$lnum:"
                echo "$line"
            fi
        fi
    done < "$1"

    shift                                         # next file
done
exit 0
