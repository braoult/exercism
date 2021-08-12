#include "raindrops.h"
#include <stdio.h>

char *convert(char result[], int drops)
{
    char *p=result;

    if (!(drops%3)) p+=sprintf(p, "%s", "Pling");
    if (!(drops%5)) p+=sprintf(p, "%s", "Plang");
    if (!(drops%7)) p+=sprintf(p, "%s", "Plong");
    if (p==result) sprintf(p, "%d", drops);
    return result;
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1, i;
    char buffer[128];

    for (; arg<ac; ++arg) {
        i=atoi(av[arg]);
        printf("raindrops(%d)=%s\n", i, convert(buffer, i));
    }
}
#endif
