#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>

#include "phone_number.h"

#define LEN_NUM   10
#define LPAREN    '('

/* this version is likely not very stable, due to poor scanf() capabilities
 * I made it to offer an option to traditional strtok() or manual string
 * parsing.
 */
static char *scan="%m[+(0-9]%*[()-. ]%m[0-9]%*[)-. ]%m[0-9]%*[-. ]%m[0-9]";

char *phone_number_clean(const char *input)
{
    char *sn[4] = { 0 };
    uint64_t num[4];
    uint64_t *p = &*num;
    int nmatch;
    char *res;

    if (!(res = malloc(LEN_NUM+1)))
        return NULL;
    memset(res, '0', LEN_NUM);
    *(res+LEN_NUM) = 0;

    nmatch = sscanf(input, scan, &sn[0], &sn[1], &sn[2], &sn[3]);

    for (int i=0; i<nmatch; ++i) {
        *(p+i) = atol(*sn[i] == LPAREN? sn[i]+1: sn[i]);
        free(sn[i]);                              /* due to scanf %m */
    }

    switch (nmatch) {
        case 2:
        case 0:
            return res;
        case 1:                                   /* full number */
            if (*p > 10000000000)                 /* 1 000 000 0000 */
                *p -= 10000000000;
            if (*p > 9999999999 ||                /* 999 999 9999 */
                *p < 2000000000)                  /* 200 000 0000 */
                return res;
            break;
        case 4:                                   /* country code */
            if (*p != 1)
                return res;
            p++;                                  /* go to area number */
            fallthrough;                          /* only gcc>=7 & clang>=12 */
        case 3:                                   /* start with area number */
            if (*p < 200 || *p > 999 ||
                *(p+1) < 200 || *(p+1) > 999 ||
                *(p+2) > 9999)
                return res;
            break;
    }
    snprintf(res, LEN_NUM+1, "%ld%ld%ld", *p, *(p+1), *(p+2));

    return res;
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg;
    char *res;

    for (arg=1; arg<ac; ++arg) {
        res=phone_number_clean(av[arg]);
        printf("orig = [%s]\n", av[arg]);
        printf("\t-> [%s]\n", res);
        free(res);
    }
}
#endif
