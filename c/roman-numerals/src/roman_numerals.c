#include "roman_numerals.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

static struct conv_s {
    unsigned char r;
    unsigned d;
} conv[] = {
    { 'M', 1000 },
    { 'D',  500 },
    { 'C',  100 },
    { 'L',   50 },
    { 'X',   10 },
    { 'V',    5 },
    { 'I',    1 }
};

/* rules could differ (like IIII/VIIII instead of IV/IX), so it is better not
 * to harcode values like 4, 9, 40, 90 etc...
 * Example: the Colosseum gate 44 was written XLIIII, and not XLIV.
 * we can therefore add a parameter in function below, and add a rule in
 * the code to easily return a different notation.
 */
char *to_roman_numeral(unsigned int n /*, int notation */ )
{
    unsigned cur=0, mult, pos=0, i;
    char res[64]={0}, *to;

    /* max number = 3999 = MMMCMXCIX */
    if (n >= 4000)                                /* could be different if we */
        return NULL;                              /* accept the 5000 sign */

    while (n) {
        /* we could : switch (notation) {
         *              case ROMAN_RULE:
         */
        if ((mult=n/conv[cur].d)) {               /* >= current multiplier */
            if (mult%5==4) {                      /* 4 & 9 */
                res[pos++]=conv[cur].r;
                res[pos++]=conv[cur-mult/4].r;    /* 4/4=1, 9/4=2 */
            } else {                              /* 1-3 & 5-8 */
                if (mult >= 5)
                    res[pos++]=conv[cur-1].r;
                for (i=mult%5; i>0; --i)
                    res[pos++]=conv[cur].r;
            }
            n-=mult*conv[cur].d;
        }
        cur+=2;
    }
    if ((to=malloc(pos+1)))
        memcpy(to, res, pos+1);
    return to;
}


/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
#include <stdlib.h>
int main(int ac, char **av)
{
    int arg=1;
    unsigned i;

    for (; arg<ac; ++arg) {
        i=atoi(av[arg]);
        printf("roman(%d)=%s\n", i, to_roman_numeral(i));
    }
}
#endif
