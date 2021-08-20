#include "hamming.h"

/* test does not include invalid input, but it should, as the subject is
 * about DNA sequence, not ASCII chars sequence :-)
 * exercism test needs only:
 *     #define V(p) (*p)
 */
#define V(p) (*(p)=='A' || *(p)=='C' || *(p)=='G' || *(p)=='T')

int compute(const char *l, const char *r)
{
    int res=0;

    if (!l || !r)
        return -1;
    for (; V(l) && V(r); ++l, ++r)
        if (*l != *r)
            res++;
    return *l || *r? -1: res;
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#if defined UNIT_TEST
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac==3) {
        printf("compute(%s, %s)=%d\n", *(av+1), *(av+2), compute(*(av+1), *(av+2)));
    }
}
#endif
