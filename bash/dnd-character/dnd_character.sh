#!/usr/bin/env bash
#
# v1: initial version
# v2: cleanup, replaced while loops with for loops when possible

# external tools: none

# set to 0 to disable log function output, 1 otherwise
debug=0

declare -a abilities=( strength dexterity intelligence wisdom charisma constitution )


usage()  {
    echo "dnd_characters.sh generate|modifier <n>" >&2
    exit 1
}

# log function takes 1 argument which is echoed if $debug is > 0
# todo: Add another argument (mask ?) to selectively log portions of code
log () {
    (( $debug )) && echo "$*"
}

# simple bubble sort for numeric array (descending)
# args: 1: the array
# todo: add a parameter for asc/desc order.
sort_n() {
    local -a array=( "$@" )
    local -i max=$(( ${#array[@]} - 1 ))

    for (( max= $(( ${#array[@]} - 1 )); max > 0; max-- )); do
        local -i i
        for (( i=0; i<max; i++ )); do
            local -i val1=${array[$i]}
            local -i val2=${array[$((i + 1))]}

            # switch if necessary
            if (( $val1 < $val2 )); then
                local tmp=$val1
                array[$i]=$val2
                array[$(($i + 1))]=$tmp
            fi
        done
    done
    echo "${array[@]}"
}

# roll $2 times a $1 faces dice
roll() {
    local -a rolls
    local -i i
    for (( i=1; i<=$2; i++ )); do
        rolls[$i]=$((RANDOM % $1 + 1))
    done

    echo ${rolls[@]}
}

modifier() {
    local -i res
    local -i in=$1
    local -i out=$(( $in - 10 ))

    log modifier in "$1"
    res=$(( $out / 2 ))                           # will alwaid round down
    log modifier div "$res"
    # adjust for negative numbers
    (( $out < 0 )) &&  (( $out % 2 )) && (( res-- ))
    log modifier adjust negative "$res"

    echo $res
}

generate() {
    local -i s
    local -a dices

    for ability in ${abilities[@]}; do
        dices=( $(roll 6 4) )
        s=( $(sort_n ${dices[@]}) )

        sum=$(( ${s[1]} + ${s[2]} + ${s[3]} ))
        echo $ability $sum

        if [[ $ability == "constitution" ]]; then
            echo "hitpoints $(( 10 - $(modifier $sum) ))"
        fi
    done
}

command="$1"
case "$command" in
    "modifier")
        (( $# != 2 )) && usage
        modifier "$2"
        ;;
    "generate")
        (( $# != 1 )) && usage
        generate
        ;;
    *)
        usage
        ;;
esac

exit 0

# Indent style for emacs
# Local Variables:
# sh-basic-offset: 4
# sh-indentation: 4
# indent-tabs-mode: nil
# comment-column: 60
# End:
