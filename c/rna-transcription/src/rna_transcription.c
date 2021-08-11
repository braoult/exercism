#include <malloc.h>
#include <string.h>
#include "rna_transcription.h"

static char C[256]={
    ['G']='C', ['C']='G', ['T']='A', ['A']='U',
};

char *to_rna(const char *dna)
{
    char *rna=malloc(strlen(dna+1)), *p;

    if (rna) {
        for (p=rna; *dna; p++, dna++) {
            if (!(*p=C[(int)*dna])) {
                free(rna);
                return NULL;
            }
        }
        *p=0;
    }
    return rna;
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;

    for (; arg<ac; ++arg) {
        printf("rna(%s)=%s\n", av[arg], to_rna(av[arg]));
    }
}
#endif
