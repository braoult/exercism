#include "grains.h"
/* See GNUmakefile in following link for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

uint64_t square(uint8_t index)
{
    return  index>0 && index <65 ? (uint64_t)1<<(index-1): 0;
}
uint64_t total(void)
{
    /* Geometric series sum formula for 64 terms, ratio 2 and first term 1:
     * S = 2⁰ + 2¹ + 2² + ... + 2⁶³
     *   = (1-2⁶⁴) / (1-2)
     *   = 2⁶⁴ - 1
     *   = 0 - 1 for uint64_t
     * We should write (2<<64)-1, but gcc won't compile, due to:
     *   -Werror=shift-count-overflow
     * Then we could avoid it by using:
     *    #pragma GCC diagnostic ignored "-Wshift-count-overflow"
     * but i think it is out of scope for this exercise (we should also take
     * care of other compilers).
     */
    return (uint64_t) -1;
}



#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    uint64_t i;

    for (; arg<ac; ++arg) {
        i=atol(av[arg]);
        printf("value(%lu)=%lu\n", i, square(i));
    }
    printf("total()=%lu\n", total());
}
#endif
