#!/usr/bin/env bash -x
shopt -s extglob
str=$1
# Brute force algorithm:
# 1 - remove all unwanted chars: keep only {}[]()
str=${str//[^\{\}\(\)\[\]]}

res=true
# 2- remove all pairs of [], {}, (). loop until string is empty (match ok) or unchanged
# (nok)
loop=1
while [[ ${#str} > 0 ]]
do
    str2=${str//+(\[\]|\(\)|\{\})}
    if [[ ${#str2} == ${#str} ]]; then
        res=false
        break
    fi
    str="$str2"
done

echo $res
exit 0
