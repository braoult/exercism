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

/* Formulas used :
 *
 *       R\c 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
 *       0   A . . . . . . . I . . . . . . . Q . . .
 *       1   . B . . . . . H . J . . . . . P . R . .
 *       2   . . C . . . G . . . K . . . O . . . S .
 *       3   . . . D . F . . . . . L . N . . . . . T
 *  NR-1=4   . . . . E . . . . . . . M . . . . . . .
 *
 * First/last R :
 *    I-A = Q-I = M-E = U-M = (NR-1)*2
 *
 * Others, flip between :
 *    H-B = G-C = F-D = P-J = O-K = N-L = (NR-R-1)*2
 * And :
 *    J-H = K-G = L-F = R-P = S-O = T-N = R*2
 */

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
