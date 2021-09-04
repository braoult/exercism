#!/bin/bash

CMD=${0##*/}
ROOT=${0%/*}

usage() {
    printf "usage: %s destination_dir\n" "$CMD"
}

if (($# == 0)); then
    "$0" "$PWD"
    exit 0
fi

if (($# != 1)) || [[ ! -d $1 ]]; then
   usage
   exit 1
fi
TEMPLATES="$ROOT/templates"

# copy GNUmakefile and br-common.h
echo -n "copying GNUmakefile and br-common.h files... "
cp -p "$TEMPLATES/"{GNUmakefile,br-common.h} "$1"
echo done.
# add include br-common.h in exercise include file
INC=${1%/}
INC=${INC##*/}
INC="$1/${INC//-/_}.h"

if [[ ! -f "$INC" ]]; then
    printf "cannot find <%s> include file\n" "$INC"
    exit 1
fi

STR='#include "br-common.h"'
# likely very weak
# TODO: check if not already inserted
#echo -n "editing $INC include file... "
#sed -i "/#define /a $STR" "$INC"
#echo done.
echo -n "editing $INC include file... "
echo "" >> "$INC"
echo "$STR" >> "$INC"
echo done.
