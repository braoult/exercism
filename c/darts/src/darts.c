#include "darts.h"

score_t scores[] ={
    { 1.0F,  10 },
    { 25.0F,  5 },
    { 100.0F, 1 },
    { -1.0F,  0 }
};

/* Below function is basically incorrect for general case.
 * However, it should mostly work here, as we compare relatively small numbers.
 * see below for better alternatives :
 * https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
 */
static inline bool float_almost_equal(float x, float y)
{
    register float f=x-y;
    return f<MIN_FLOAT_EQUAL && f>-MIN_FLOAT_EQUAL? true: false;
}

unsigned score(coordinate_t c)
{
    float x=c.x, y=c.y, radius=x*x+y*y;
    int i;

    for (i=0; scores[i].score; ++i) {
        if (float_almost_equal(radius, scores[i].radius) || radius < scores[i].radius)
            break;
    }
    return scores[i].score;
}

#ifdef UNIT_TEST
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av)
{
    int arg=1;
    float x, y;

    for (; arg<ac-1; ++arg, ++arg) {
        x=atof(av[arg]);
        y=atof(av[arg+1]);
        printf("equal(%f, %f)=%d\n", x, y, float_almost_equal(x, y));
    }

}
#endif
