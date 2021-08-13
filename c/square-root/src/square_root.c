#include "square_root.h"

/* V1: initial version
 * V2: fix end condition: fail when i/2 < sqrt(i), for instance for i=2
 * V3: improve seed determination: 60-70% improvement.
 */

/* See GNUmakefile in following link for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

#define NBITS (sizeof(unsigned) * 8)

/* Newton's method:
 * https://en.wikipedia.org/wiki/Newton%27s_method#Square_root
 * return the largest integer equal or less than i square root.
 */
unsigned square_root(unsigned i)
{
    unsigned sq, sq2;
    unsigned j;
    long max;

    if (i<=1)                                     /* 0 and 1 */
        return i;

    //nbits = (sizeof(unsigned) * 8);
    for (j = 4, max = 16L;; j += 2, max <<= 2L) {
        if (j >= NBITS || i <= max) {
            sq2 = (1L << (j >> 1));
            break;
        }
    }
    do {
        sq = sq2;
        sq2 = ((i/sq) + sq) / 2;                  /* next iteration */
    } while (sq2<sq);
    return sq;
}

#ifdef UNIT_TEST
int main(int ac, char **av)
{
    unsigned i, j;

    if (ac && *av)
        for (i=0; i<100000000; ++i)
            square_root(65025);
    printf("sq=%u\n", square_root(65536));
}
#endif
