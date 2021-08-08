#!/usr/bin/env bash

num=$1

strings=(
    "wink"
    "double blink"
    "close your eyes"
    "jump"
)
reverse=n
result=()

(( $num & 2#10000 )) && reverse=y

# get matching bits
for (( i=0 ; i<4 ; ++i )); do
    (( $num & 1<<$i )) && result+=( "${strings[$i]}" )
done
# output in normal or reverse order
for (( i=0 ; i<${#result[@]} ; ++i)) ; do
    [[ $reverse == n ]] && echo -n "$sep${result[i]}" || echo -n "$sep${result[~i]}"
    sep=","
done
echo
exit 0
