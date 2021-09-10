#include "run_length_encoding.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* We have 2 choices for encoding : allocate a max length string (i.e. the
 * size of input string), maybe shrinking with realloc() before returning or
 * trying to calculate first the the exact output length.
 *
 * For decoding, if we want to avoid an arbitrary MAX_LENGTH, or, worse,
 * a smaller string with multiple realloc() when we need more space, we
 * also can first calculate the output string size.
 *
 * We will go for the second method (calculate exact length first for both
 * encode() and decode().
 *
 * Additional checks: we allow only printable characters (isprint()), and
 * disallow digits for encode() and ending digits for decode().
 */

int encode_len(const char  *str)
{
    int len=0,  c;

    if (!str)
        return -1;
    for (c=*str; c; c=*str) {
        int sublen=0, log=1;
        if (isdigit(c) || !isprint(c))
            return -1;
        for (; *str == c; str++, sublen++)
            ;
        if (sublen > 1)
            do
                log++;
            while (sublen /= 10);
        len += log;
    }
    return len+1;
}

char *encode(const char *str)
{
    char *res, *p;
    int c, len;

    if (!(str && (len = encode_len(str)) > 0 && (res = malloc(len))))
        return NULL;
    p=res;

    for (c=*str; c; *p++ = c, c=*str) {
        int sublen = 0;
        for (; *str == c; str++, sublen++)        /* count consecutive chars */
            ;
        if (sublen > 1)
            p += sprintf(p, "%d", sublen);
    }
    *p = 0;
    return res;
}

int decode_len(const char  *str)
{
    int len=0;

    if (!str)
        return -1;
    for (int c = *str; c; c = *++str, len++) {
        if (isdigit(c)) {
            int sublen = strtold(str, (char **)&str);
            if ((c = *str) == 0 || !isprint(c))   /* the char to duplicate */
                return -1;
            len += sublen - 1;
        }
    }
    return len+1;
}


char *decode(const char *str)
{
    char *res, *p;
    int len;

    if (!(str && (len = decode_len(str)) > 0 && (res = malloc(len))))
        return NULL;
    p=res;

    for (int c = *str; c; *p++ = c, c = *++str) {
        if (isdigit(c)) {
            int sublen = strtold(str, (char **)&str);
            c = *str;                             /* the char to duplicate */
            while (--sublen)                      /* or (optimized) memset ? */
                *p++ = c;
        }
    }
    *p = 0;
    return res;
}
