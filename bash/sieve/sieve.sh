#!/usr/bin/env bash

usage() {
    echo "Usage: ./seave.sh <number>"
    exit 1
}
end=$1

[[ ! "$end" =~ ^[[:digit:]]*$ ]] && usage

declare -a numbers

sep=""
for (( i=2; i<=end; ++i )); do
    if [[ ${numbers[$i]} == "" ]]; then
        echo -n "$sep$i"
        for (( j=i*2; j<=end; j+=i )); do
            numbers[$j]=t
        done
        sep=" "
    fi
done
echo
exit 0
