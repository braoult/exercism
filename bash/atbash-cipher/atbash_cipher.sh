#!/usr/bin/env bash
#
# External tools: none.
# Subshell: no.
#
# Tested on: bash 5.0, 3.2
#
# V1: initial version
# V2: changed +() to @() in args check. Fixed typo on lines 48-52 formulas.

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
    die "usage: atbash_cypher.sh encode|decode text [...]"
}

# we will accept the syntax:
# atbash_cypher.sh encode|decode text [...]
# in case text is separated as multiple arguments, we will consider a space is
# in between.
# example:
#   atbash_cypher.sh encode "I am happy"
# will also be accepted as:
#   atbash_cypher.sh encode I am happy

# basic args check & set all chars to lowercase
(($# < 2)) || [[ "$1" != @(encode|decode) ]] && usage
action="$1"
shift
string="${*,,}"
len="${#string}"
debug 1 "string=$string" "len=$len"

# algorithm we will use:
# to get rev element c' of c in a consecutive integer n-m list :
#     c    = n+i                        i is distance from n to c
#     c'   = m-i                        and also reverse distance from m to c'
#     ------------
#     c+c' = n+m                        sum the 2
#     c'   = n+m-c                      after simplification

# for printf, a '<char> arg is the ascii value of <char>
# and yes, we should use a constant, any programmer knows ascii value of 'a'
# and # of letters in alphabet, we could simply set tval to 219
printf -v aval "%d" "'a"                # 'a' ascii value
printf -v zval "%d" "'z"                # 'z' ascii value
printf -v tval "%d" $((aval+zval))      # their sum

# tval=219                              # correct code for this exercise, for me

debug 1 "aval:$aval zval:$zval tval:$tval"

# many options here:
#   - for encode, add <spaces> in loop, or at the end
#   - use a table with all alphabet ({a..z}), to avoid multiple printf
#   - fill acceptable chars only (my choice), insert spaces at end.
#     I preferred that one to avoid multiple encode/decode tests in loop.
#   - likely many others
result=""                               # resulting string, with no spaces
for ((i=0; i<len; ++i)); do
    c=${string:$i:1}                    # current char
    printf -v cval "%d" "'$c"           # $c's ascii value
    debug 2 "c='$c' cval=$cval"

    case "$c" in
        [[:alpha:]])                    # rev $c's in alphabet (with hex value)
            printf -v rval "%x" $((tval - cval))
            printf -v c "\\x$rval"      # shellcheck unhappy here
            debug 4 "rev c=$c"
            ;;
        [![:digit:]])                   # we avoid 1 case (digits)
            continue
            ;;
    esac
    result+="$c"
done

# for encoding, we split in 5 chars groups.
if [[ $action == encode ]]; then
    [[ $result =~ ${result//?/(.)} ]]
    # we use REMATCH here, to avoid loop, but we could end with a space.
    printf -v result "%c%c%c%c%c " "${BASH_REMATCH[@]:1}"
fi

debug 1 "result: =${result%% }="
echo "${result%% }"                     # fix possible REMATCH extra final space
exit 0

# emacs/vim settings.
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 40
# fill-column: 80
# End:
# vim: set tabstop=4 expandtab:
