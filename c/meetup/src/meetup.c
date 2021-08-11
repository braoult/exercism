#include "meetup.h"
#include <time.h>
#include <stdlib.h>

/* The explanation tells about 'fifth', not included in tests.
 * I will manage this, returning "-1" if it does not exist.
 */

/* convert the 2/3 first chars of string to big endian integer */
#define S2BE(a, b) ((a<<8)+b)
#define S3BE(a, b, c) ((a<<16)+(b<<8)+c)

#define TEENTH 42
#define LAST   21

static int str2day(const char *d)
{
    switch (S2BE(*d, *(d+1))) {
        case S2BE('M', 'o'): return 1;
        case S2BE('T', 'u'): return 2;
        case S2BE('W', 'e'): return 3;
        case S2BE('T', 'h'): return 4;
        case S2BE('F', 'r'): return 5;
        case S2BE('S', 'a'): return 6;
        case S2BE('S', 'u'): return 0;
    }
    return -1;
}

static int str2nth(const char *d)
{
    switch (S3BE(*d, *(d+1), *(d+2))) {
        case S3BE('f', 'i', 'r'): return 0;
        case S3BE('s', 'e', 'c'): return 1;
        case S3BE('t', 'h', 'i'): return 2;
        case S3BE('f', 'o', 'u'): return 3;
        case S3BE('f', 'i', 'f'): return 4;
        case S3BE('l', 'a', 's'): return LAST;
        case S3BE('t', 'e', 'e'): return TEENTH;
    }
    return -1;
}

static int m_1st(unsigned y, unsigned m)
{
    struct tm time = {
        .tm_year=y-1900,
        .tm_mon=m-1,
        .tm_mday=1
    };
    mktime (&time);
    return time.tm_wday;
}

static int m_ndays(unsigned y, unsigned m)
{
    static int days[]={31, 42, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return m!=2 ? days[m-1]:
        (!(y % 4) && (y % 100 || !(y % 400)))? 29: 28;

}

int meetup_day_of_month(unsigned int yy, unsigned int mm, const char *sweek,
                        const char *sday)
{

    int nth, ndays, wanted, res=-1;

    ndays=m_ndays(yy, mm);
    if ((nth=str2nth(sweek))<0 || (wanted=str2day(sday))<0)
        return -1;
    if ((res=wanted-m_1st(yy, mm)+1) <= 0)
        res+=7;

    if (nth<5) {
        if ((res+=7*nth)>ndays)
            res=-1;
    } else if (nth==TEENTH) {
        if ((res+=7)<13)
            res+=7;
    } else {                                      /* last */
        if ((res+=7*4)>ndays)
            res-=7;
    }

    return res;
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    unsigned y, m;

    for (; arg<ac-3; arg+=4) {
        y=atoi(av[arg]);
        m=atoi(av[arg+1]);
        printf("meetup(%d, %d, %s, %s)=%d\n",
               y, m, av[arg+2], av[arg+3],
               meetup_day_of_month(y, m, av[arg+2], av[arg+3]));
    }
}
#endif
