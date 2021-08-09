#include "gigasecond.h"

/* See GNUmakefile in following link for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

time_t gigasecond_after(time_t t)
{
    return t+1e9;
}

#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    unsigned long i;
    for (; arg<ac-1; ++arg) {
        i=atol(av[arg]);
        printf("giga(%lu)=%lu\n", i, gigasecond_after(i));
    }
}
#endif
