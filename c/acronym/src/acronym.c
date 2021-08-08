#include <string.h>
#include <malloc.h>
#include <ctype.h>

#include "acronym.h"

/* See GNUmakefile in following link for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

#define SKIPWORD(p) { while (*(p) && (isalpha(*(p)) || *p=='\'')) (p)++;}
#define NEXTWORD(p) { while (*(p) && !isalpha(*(p))) (p)++;}

char *abbreviate(const char *phrase)
{
    /* Yet another approach (to avoid scanning phrase twice):
     * We (re)allocate a ALLOCSIZE buffer when current one is not large
     * enough to accept next character + 1 ('\0')
     *
     * Other solutions would be to scan phrase twice (for example an initial
     * strlen() to find out a maximum length), or the (bad idea) using a fixed
     * size buffer.
     *
     * The usual choices.
     */
    char *buf=NULL;
    int c=0, size=0;

    if (!phrase)
        return NULL;

    while (*phrase) {
        NEXTWORD(phrase);
        if (*phrase) {
            /* buffer too small */
            if (c>=size-1) {
                size+=ALLOCSIZE;
                if (!(buf=realloc(buf, size)))
                    return NULL;
            }
            *(buf+c++)=toupper(*phrase++);
            SKIPWORD(phrase);
        }
    }

    /* at least one character */
    if (c)
        *(buf+c)=0;
    return buf;
}

#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    char *p;

    for (; arg<ac; ++arg) {
        p=abbreviate(*(av+arg));
        printf("acronym(%s)=[%s]\n", *(av+arg), p? p: "NULL");
        if (p)
            free(p);
    }
}
#endif
