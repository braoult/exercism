#include <stdio.h>
#include <malloc.h>

/* V1: initial version
 * V2: bug fix: force full unsigned allocation instead of bytes.
 */
#include "sum_of_multiples.h"

#define BITS (sizeof(unsigned)*8)

#define getbit(i) (!!(sieve[(i) / BITS] & (1 << ((i) % BITS))))
#define setbit(i) (sieve[(i) / BITS] |= (1 << ((i) % BITS)))

/* use a kind of eratosthenes's sieve, to avoid the trivial solution :-)
 */
unsigned sum(const unsigned *f, const size_t n, const unsigned l)
{
    unsigned sieve_size = (l-1)/BITS+1;
    unsigned num, i, res=0;
    unsigned *sieve;

    sieve = calloc(sieve_size, sizeof(unsigned)); /* l bits array */
    if (!sieve)
        return 0;
    for (i=0; i<n; ++i) {
        if (f[i]) {
            for (num=f[i]; num<l; num+=f[i]) {
                if (!getbit(num)) {
                    res+=num;
                    setbit(num);
                }
            }

        }
    }
    free(sieve);
    return res;
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    unsigned input[256];
    int last, i;
    if (ac>2) {
        last=atol(av[1]);
        for (i=2; i<ac; ++i) {
            input[i-2]=atoi(av[i]);
        }
        printf("sum(..., %u, %u)=%u\n", i-2, last,
               sum(input, (unsigned)i-2, (unsigned)last));
    }
}
#endif
