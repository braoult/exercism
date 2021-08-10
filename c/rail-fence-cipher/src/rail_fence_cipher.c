#include "rail_fence_cipher.h"
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

char *doit(char *t, size_t nr, int what)
{
    int tlen=strlen(t);
    unsigned cchar=0, r;
    char *res;

    if (!(res=malloc(tlen+1)))
        return NULL;
    for (r=0; r<nr; ++r) {
        bool flip=false;
        int pchar=r;
        while (pchar<tlen) {
            if (what==ENCODE)
                res[cchar]=t[pchar];
            else
                res[pchar]=t[cchar];
            cchar++;
            if (r>0 && r<nr-1) {
                pchar+=flip ? r*2: (nr-r-1)*2;
                flip=!flip;
            } else {
                pchar+=(nr-1)*2;
            }

        }
    }
    res[tlen]=0;
    return res;
}

#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    int i;
    char *p, *q;
    for (; arg<ac-1; ++arg, ++arg) {
        p=av[arg];
        i=atoi(av[arg+1]);
        printf("encode(%s, %d)=%s\n", p, i, q=encode(p, i));
        printf("decode(%s, %d)=%s\n", q, i, decode(q, i));
    }
}
#endif
