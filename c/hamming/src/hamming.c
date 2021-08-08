#include "hamming.h"

/* Note: For explanation on section below, see 'GNUfilename' included in
 * link below :
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

/* test does not include invalid input, but it should, as the subject is
 * about DNA sequence, not ASCII chars sequence :-)
 * exercism test needs only:
 *     #define V(p) (*p)
 */
#define V(p) (*(p)=='A' || *(p)=='C' || *(p)=='G' || *(p)=='T')

int compute(const char *lhs, const char *rhs)
{
    int res=0;
    const char *l=lhs, *r=rhs;

    if (!l || !r)
        return -1;
    for (; V(l) && V(r); ++l, ++r) {
        if (*l != *r)
            res++;
    }
    return *r || *l? -1: res;
}


#ifdef UNIT_TEST
int main(int ac, char **av)
{
    if (ac==3) {
        printf("compute(%s, %s)=%d\n", *(av+1), *(av+2), compute(*(av+1), *(av+2)));
    }
}
#endif
