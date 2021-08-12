#include "leap.h"

/* already dont in meetup exercise */
bool leap_year(int y)
{
    return ((y % 4) ||
            (y % 400 && !(y % 100)))? false: true;
}


/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1, i;

    for (; arg<ac; ++arg) {
        i=atoi(av[arg]);
        printf("leap_year(%d)=%d\n", i, leap_year(i));
    }
}
#endif
