#include "binary_search.h"

const int *binary_search(int v, const int *a, size_t size)
{
    size_t lo, hi, i;

    /* quickly exclude invalid/trivial results :
     * NULL or empty array, value out of bounds
     */
    if (!size || !a || v < *a || v > *(a+size-1))
        return NULL;
    for (lo=0, hi=size-1, i=hi/2; lo<hi && a[i]!=v; i=lo+(hi-lo)/2) {
        if (a[i] < v)
            lo=i+1;
        else
            hi=i-1;
    }
    return a[i]==v? a+i: NULL;
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
#include <stdio.h>
int main(int ac, char **av)
{
    int arg=1, *res;
    int i, array[] = {1, 2, 3, 4, 6, 7, 8, 9 };
    size_t size = sizeof(array) / sizeof(array[0]);

    for (; arg<ac; ++arg) {
        i=atoi(av[arg]);
        res=binary_search(i, array, size);
        printf("binary_search(%d)=%ld\n", i,
               res? res-array: -1);
    }
}
#endif
