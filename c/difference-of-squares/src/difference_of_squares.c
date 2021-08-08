#include "difference_of_squares.h"

/* See GNUmakefile in following link for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

unsigned int sum_of_squares(unsigned int number)
{
    /* the sum of 1st n integers squares is:
     *  S = 1² + 2² + 3² ..... + (n-1)² + n²
     *    = [ n * (n+1) * (2n+1) ] / 6
     * some visual explanations on:
     *   http://www.takayaiwamoto.com/Sums_and_Series/sumsqr_1.html
     */
    return number * (number+1) * (2*number + 1) / 6;
}

unsigned int square_of_sum(unsigned int number)
{
    register int res;
    /* The sum of n 1st integers is:
     *  S  = 1 + 2 + 3 ... + (n-1) + n
     *     = [ n * (n+1) ] / 2
     * demonstration is trivial for this one.
     */
    res=number * (number+1) / 2;
    return res*res;
}

unsigned int difference_of_squares(unsigned int number)
{
    return square_of_sum(number) - sum_of_squares(number);
}

#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    int i;

    for (; arg<ac; ++arg) {
        i=atoi(av[arg]);
        printf("sumsq(%d)=%d\n", i, sum_of_squares(i));
        printf("sqsum(%d)=%d\n", i, square_of_sum(i));
        printf("diff(%d)=%d\n", i, difference_of_squares(i));
    }
}
#endif
