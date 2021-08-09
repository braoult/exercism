#include "pangram.h"
#include <ctype.h>
/* See GNUmakefile in following link for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

bool is_pangram(const char *sentence)
{
    char result['z'-'a'+1]= { 0 }, c;
    /* count is used to avoid parsing whole string: we stop when all
     * letters found
     */
    int count=0;

    if (sentence) {
        for (; *sentence && count<26; ++sentence) {
            if (isalpha(*sentence)) {
                c=tolower(*sentence);
                if (!result[c-'a']) {
                    result[c-'a']=1;
                    count++;
                }
            }
        }
    }
    return count==26;
}

#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    for (; arg<ac; ++arg) {
        printf("pangram(%s)=%d\n", av[arg], is_pangram(av[arg]));
    }
}
#endif
