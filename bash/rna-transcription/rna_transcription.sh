#!/usr/bin/env bash
#
# External tools: none.
#
# V1: initial version

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
    die "usage: rna_transcription.sh [seq1] [...]"
}

declare -A complement=([G]='C'
                       [C]='G'
                       [T]='A'
                       [A]='U')
debug 1 keys/vals=${!complement[@]}/${complement[@]}
# we will accept multiple args (out of topic for exercise), meaning that:
#  rna_transcription.sh GCTA
# is equivalent to
#  rna_transcription.sh G C T A
# or
#  rna_transcription.sh G CTA
dna="${@}"
dna="${dna// /}"                        # remove spaces
(($# > 0 )) && [[ "$dna" != +([GCTA]) ]] && die "Invalid nucleotide detected."

((ldna=${#dna}))
debug 1 "dna=$dna, length=$ldna"
rna=""                                  # rna sequence

for ((i=0; i<ldna; ++i)); do
    seq=${dna:$i:1}
    rna+="${complement[$seq]}"
    debug 2 "rna=$rna"
done

echo "$rna"                             # not perfect, empty line if no args.
exit 0

# emacs/vim settings.
# Local Variables:
# sh-basic-offset: 4
# indent-tabs-mode: nil
# comment-column: 40
# fill-column: 80
# End:
# vim: set tabstop=4 expandtab:
