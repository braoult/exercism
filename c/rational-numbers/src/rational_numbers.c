#include "rational_numbers.h"
#include <stdlib.h>
#include <math.h>

#define N(r)  ((r).numerator)
#define D(r)  ((r).denominator)

/* Note. We should probably check for possible overflow in all
 * functions below (not covered in exercise).
 * To do this, a simple solution could be to make operations with
 * long long (or some other method), and add a field in rational_t
 * to express such overflow, division by zero, etc...
 */

/* Euclidean algorithm (by Donald Knuth) */
rational_t reduce(rational_t r)
{
    int16_t a=abs(N(r)), b=abs(D(r)), t;

    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    if (D(r) < 0)
        a=-a;
    return (rational_t) { N(r)/a, D(r)/a };
}

/* to avoid pow() for integers
 * BUG: does not check for overflow
 */
static inline int power(int n, int p)
{
    int res=n;

    if (p==0)
        return 1;
    while (--p)
        res*=n;
    return res;
}

/* All formulas below come from https://en.wikipedia.org/wiki/Rational_number
 */
rational_t add(rational_t r1, rational_t r2)
{
    return reduce((rational_t) {
            N(r1) * D(r2) + N(r2) * D(r1),
            D(r1) * D(r2)
        });
}

rational_t subtract(rational_t r1, rational_t r2)
{
    return reduce((rational_t) {
            N(r1) * D(r2) - N(r2) * D(r1),
            D(r1) * D(r2)
        });
}

rational_t multiply(rational_t r1, rational_t r2)
{
    return reduce((rational_t) {
            N(r1) * N(r2),
            D(r1) * D(r2)
        });
}

rational_t divide(rational_t r1, rational_t r2)
{
    return reduce((rational_t) {
            N(r1) * D(r2),
            D(r1) * N(r2)
        });
}

rational_t absolute(rational_t r)
{
    return (rational_t) {
        abs(N(r)),
        abs(D(r))
    };
}

rational_t exp_rational(rational_t r, uint16_t n)
{
    return reduce((rational_t) {
            power(N(r), n),
            power(D(r), n)
        });
}

float exp_real(uint16_t x, rational_t r)
{
    return powf((float)x, (float)N(r)/D(r));
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    rational_t r1, r2;

    for (; arg<ac-1; ++arg, ++arg) {
        r1.numerator=atoi(av[arg]);;
        r1.denominator=atoi(av[arg+1]);;
        r2=reduce(r1);
        printf("reduce(%d, %d)=(%d, %d)\n", N(r1), D(r1), N(r2), D(r2));
    }
}
#endif
