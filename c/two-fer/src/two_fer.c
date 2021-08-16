#include <stdio.h>
#include "two_fer.h"

#define BUFFER_SIZE 100                           /* in test program */
#define USED "One for , one for me."
#define MAXLEN (int)(100-sizeof(USED))


void two_fer(char *buf, const char *name)
{
    /* Ensure we do not overflow the test buffer:
     * Return string is at most (BUFFER_SIZE-1) characters, that is
     * BUFFER_SIZE including final '\0'.
     */
    sprintf(buf, "One for %.*s, one for me.", MAXLEN, name&&*name? name: "you");
}


/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
#include <string.h>
int main(int ac, char **av)
{
    int arg=1;
    char foo[200];

    printf("MAXLEN=%d\n", MAXLEN);
    for (; arg<ac; ++arg) {
        two_fer(foo, av[arg]);
        printf("two_fer= len=%lu str=[%s]\n", strlen(foo), foo);
    }
}
#endif
