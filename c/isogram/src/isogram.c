#include "isogram.h"
#include <ctype.h>

#define POS(c) (tolower(c)-'a')

/* This does not work outside English world */
bool is_isogram(const char phrase[])
{
    //int map['z'-'a'+1]={0};
    int map[1000]={0};
    const char *p=phrase;

    if (!p)
        return false;
    for (; *p; ++p) {
        if (*p==' ' || *p=='-')
            continue;
        if (!isalpha((unsigned char)*p) || (++map[POS((unsigned char)*p)])>1)
            return false;
    }
    return true;
}

#ifdef UNIT_TEST
#include <stdio.h>
int main(int ac, char **av)
{
    int arg=1;

    for (; arg<ac; ++arg) {
        printf("isogram[%s]=%d\n", av[arg], is_isogram(av[arg]));
    }
}
#endif
