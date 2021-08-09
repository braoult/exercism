#include <time.h>
#include "space_age.h"

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

static float relative[] = {
    0.2408467,
    0.61519726,
    1.0,
    1.8808158,
    11.862615,
    29.447498,
    84.016846,
    164.79132
};
#define EARTH_SECS 31557600

float age(planet_t p, int64_t s)
{
    return s/EARTH_SECS/relative[p];
}

#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1, i;
    float f;

    for (; arg<ac-1; ++arg, ++arg) {
        i=atoi(av[arg]);
        f=atof(av[arg+1]);
        printf("age(%d, %f)=%f\n", i, f, age(i, f));
    }
}
#endif
