#!/usr/bin/env bash
# v1:   - initial version
# v2-3: - backport bubble sort (while -> for) & debug system from next exercises
#       - always read from stdin
#       - some syntax improvement
# v4:   - cosmetic/syntax changes
#       - change from empty file handling (empty string becomes valid filename)
# v5:   - cosmetic changes following "shellcheck" usage.
# v6:   - removed debug calls.
# v7-8: - cosmetic changes

die() {
    echo "${@}" >&2
    exit 1
}

# the results, associative arrays with team name as key. Some tables look
# redundant, but easier to understand.
declare -A mp                                               # matches played
declare -A win                                              # matches won
declare -A draw                                             # matches tied
declare -A loss                                             # matches lost
declare -A points                                           # points
declare -a order                                            # final order.

nteams=0

# create a team entry in arrays if non existent. $1: team
create_team() {
    if ! [[ -v "mp[$1]" ]]; then
        (( nteams++ ))
        (( mp["$1"]=0 ))
        (( win["$1"]=0 ))
        (( loss["$1"]=0 ))
        (( draw["$1"]=0 ))
        (( points["$1"]=0 ))
        order[$nteams]="$1"
    fi
}

# update results for a team: $1, $2: teams, $3: result for $1: win/draw/loss
update_results() {
    create_team "$1"
    create_team "$2"

    ((mp["$1"]++))
    ((mp["$2"]++))
    case "$3" in
        win)
            ((win["$1"]++))
            ((loss["$2"]++))
            ((points["$1"]+=3))
            ;;
        loss)
            ((win["$2"]++))
            ((loss["$1"]++))
            ((points["$2"]+=3))
            ;;
        draw)
            ((draw["$1"]++))
            ((draw["$2"]++))
            ((points["$1"]++))
            ((points["$2"]++))
            ;;
        *)                                        # should not happen
            die "fatal: invalid result $3, exiting."
    esac
}

# inspired from https://stackoverflow.com/questions/7442417/how-to-sort-an-array-in-bash
# (bubble sort)
sort_teams()
{
    local max i

    for ((max=nteams; max>0; max--)); do
        for ((i=1; i<max; ++i )); do
            local team1=${order[$i]} team2=${order[$i + 1]} switch=0

            if (( ${points["$team1"]} < ${points["$team2"]} )) || \
                   ( (( ${points["$team1"]} == ${points["$team2"]} )) && \
                         [[ "$team1" > "$team2" ]] ); then
                order[$i]="$team2"
                order[$i + 1]="$team1"
            fi
        done
    done
}

output() {
    printf "%-30s |%3s |%3s |%3s |%3s |%3s\n" "${@:1:6}"
}

output_team() {
    output "$1" "${mp[$1]}" "${win[$1]}" "${draw[$1]}" "${loss[$1]}" "${points[$1]}"
}

# output teams, according to "order" table
output_teams() {
    local i
    # header
    output "Team" "MP" "W" "D" "L" "P"
    for (( i=1; i<= nteams; ++i )); do
        output_team "${order[$i]}"
    done
}

load_teams() {
    # set separator. Note we ignore escaping ';': a\;a;b;win wont work
    local team1 team2 result
    local IFS=$';\n'

    while read -r team1 team2 result ; do
        # should empty result considered as error or ignored? Ignored here.
        [[ -z "$team1" || -z "$team2" || -z "$result" ]] && continue
        update_results "$team1" "$team2" "$result"
    done
}

# we will accept both argument (file name) or stdin input
if (( $# == 0 )); then
    load_teams
elif [[ -f "$1" ]]; then
    load_teams < "$1"
else
    die Invalid "[$1]" file. Exiting.
fi

sort_teams
output_teams

exit 0
