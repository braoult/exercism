#include <ctype.h>
#include "bob.h"

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
#include <stdio.h>
int main(int ac, char **av)
{
    int arg=1;

    for (; arg<ac; ++arg) {
        printf("bob(%s)=%s\n", av[arg], hey_bob(av[arg]));
    }
}
#endif
