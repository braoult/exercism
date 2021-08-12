#include "beer_song.h"
#include <stdio.h>

static char *fmt1="%s bottle%s of beer on the wall, %s bottle%s of beer.\n" \
    "Take %s down and pass it around, %s bottle%s of beer on the wall.\n%s";
static char *fmt2="%s bottle%s of beer on the wall, %s bottle%s of beer.\n" \
    "%sGo to the store and buy some more, %s bottle%s of beer on the wall.\n%s";

void recite(unsigned int start, unsigned int down, char *buffer)
{
    char n1[16], n2[16];
    char *p=buffer;

    while (down--) {
        sprintf(n1, "%d", start);
        sprintf(n2, "%d", start>1? start-1: 99);

        p+=sprintf(p, start? fmt1: fmt2,
                   start? n1: "No more", start==1? "": "s", start? n1: "no more",
                   start==1? "": "s",
                   start==1? "it": start? "one": "", start-1? n2: "no more",
                   start==2? "": "s", down? "\n": "");
        start=start? start-1: 99;
    }
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    unsigned i, j;
    char buffer[1024];

    for (; arg<ac-1; ++arg, ++arg) {
        i=atoi(av[arg]);
        j=atoi(av[arg+1]);
        recite(i, j, buffer);
        printf("recite(%d, %d):\n%s", i, j, buffer);
    }
}
#endif
