#include <stdio.h>
#include <stdlib.h>
#include "armstrong_numbers.h"

static inline int power(int n, int p) {
    int res=n;

    /* useless here
     * if (p==0)
     *   return 1;
     */
    while (--p)
        res*=n;
    return res;
}

bool is_armstrong_number(int candidate)
{
    int p=1, r=0, tmp=candidate;

    while (tmp/=10)
        p++;

    for (tmp=candidate; tmp; tmp /=10)
        r+=power(tmp%10, p);
    return r==candidate;
}

#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1, n;

    for (; arg<ac; ++arg) {
        n=atoi(av[arg]);
        printf("armstrong(%d)=%d\n", n, is_armstrong_number(n));
    }

}
#endif
