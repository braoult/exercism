#!/usr/bin/env bash
# V1: original version
# V2: final printf changeto avoid subshell

# external tools: none

# v1: initial version

# set to mask to enable logs
debug=0

shopt -s extglob

usage()  {
    echo "acronym.sh word1 [...]" >&2
    exit 1
}

# $1: log level, then strings to display.
log () {
    (( debug & $1 )) && shift && echo "${@}"
}


# check for basic errors. We will accept multiple args:
# acronym.sh i love suchi = acronym "i love suchi"
(( $# < 1 )) && usage

# valid word separators
VALID_SEPARATORS="-_*"

# replace valid chars with space, merge args in 1 string
words="${*//[$VALID_SEPARATORS]/ }"
log 1 valid separators ${#words[@]} "$words"

# remove remaining non alpha chars (keep blanks)
words="${words//[^[:alpha:][:blank:]]/}"
log 1 keep alpha "${words[@]}"

# capitalize, make an array
words=(${words^^})
log 1 "words ${#words[@]} ${words[@]}"

# print 1st chars
printf -v result "%c" ${words[@]}
log 1 result "$result"

echo "$result"

exit 0

# Indent style for emacs
# Local Variables:
# sh-basic-offset: 4
# sh-indentation: 4
# indent-tabs-mode: nil
# comment-column: 60
# End:
