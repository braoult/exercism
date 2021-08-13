#include <ctype.h>
#include "bob.h"
#include <stdio.h>

char*answers[] = {
    "Whatever.",
    "Sure.",
    "Whoa, chill out!",
    "Calm down, I know what I'm doing!",
    "Fine. Be that way!"
};

char *hey_bob(char *w)
{
    int yell=2, question=0, empty=4, text=0;
    for (;*w; w++) {
        if (!isspace(*w)) {
            empty=0;
            if (isalpha(*w))  text=2;
            if (islower (*w)) yell=0;
            question=*w=='?'? 1: 0;
        }
    }
    return answers[(text&yell)|question|empty];
}


/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    resistor_band_t i[2];

    for (; arg<ac-1; ++arg, ++arg) {
        *i=atoi(av[arg]);
        *(i+1)=atoi(av[arg+1]);
        printf("color(%d, %d)=%d\n", i[0], i[1], color_code(i));
    }
}
#endif
