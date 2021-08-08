#include "square_root.h"

/* See GNUmakefile in following link for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

/* Newton's method:
 * https://en.wikipedia.org/wiki/Newton%27s_method#Square_root
 * return the largest integer equal or less than i square root.
 */
unsigned square_root(unsigned i)
{
    unsigned sq, sq2;

    if (i<=1)                                     /* 0 and 1 */
        return i;

    sq = i/2;                                     /* we take i/2 as initial seed */
    sq2 = ((i/sq) + sq) / 2;                      /* first iteration */

    while (sq2 != sq) {
        sq = sq2;
        sq2 = ((i/sq) + sq) /2;                   /* next iteration */
    }

    return sq;
}

#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    unsigned i;

    for (; arg<ac; ++arg) {
        i=atol(av[arg]);
        printf("sqrt(%u)=%u\n", i, square_root(i));
    }
}
#endif
