#include <malloc.h>
#include "secret_handshake.h"

static const char *C[] = { "wink", "double blink", "close your eyes", "jump" };

const char **commands(size_t n)
{
    int i=0, c=0, s=1, e=4;
    const char **r=calloc(4, sizeof(char *));

    if (n & 020) i=3, s=-1, e=-1;                 /* reverse loop params */

    for (; i!=e; i+=s)
        if (n & (1<<i))
            r[c++]=*(C+i);
    return r;
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    int i;
    const char **res;
    for (; arg<ac-1; ++arg, ++arg) {
        i=atoi(av[arg]);
        res=commands(i);
        printf("handshake(%d)=\n", i);
        for (i=0; res[i]; ++i)
            printf("[%s] ", res[i]);
        putchar('\n');
        free(res);
    }
}
#endif
