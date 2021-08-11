#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "nucleotide_count.h"

typedef unsigned char uchar;

static int C[256] = {
    ['A']=1, ['C']=2, ['G']=3, ['T']=4
};

/* not in C99: we implement asprintf */
static char *asprintf(const char *fmt, ...)
{
    int n = 0;
    char *p = NULL;
    va_list ap;

    va_start(ap, fmt);
    n = vsnprintf(p, 0, fmt, ap);
    va_end(ap);

    if (n < 0 || !(p=malloc(n+1)))
        return NULL;

    va_start(ap, fmt);
    n = vsnprintf(p, n+1, fmt, ap);
    va_end(ap);
    if (n < 0) {
        free(p);
        return NULL;
    }

    return p;
}

char *count(const char *dna)
{
    int res[4]={ 0 };

    if (!dna)
        return NULL;                              /* should it be "" ? */

    for (const uchar *p=(uchar *)dna; *p; ++p) {
        if (!C[*p])
            return asprintf("");
        res[C[*p]-1]++;
    }
    return asprintf("A:%d C:%d G:%d T:%d", res[0], res[1], res[2], res[3]);
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    char *p;

    //printf("%s: %s\n", asprintf("%d %d %d %d %s", (long)av-(long)av, ac, arg, 1000, "foobar"));
    for (; arg<ac; ++arg) {
        p=count(av[arg]);
        printf("%s: [%s] len=%lu\n", av[arg], p, strlen(p));
    }
}
#endif
