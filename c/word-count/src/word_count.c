#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "word_count.h"
#include "hash.h"

/* See GNUmakefile in following link for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdlib.h>
#endif

/* Some cases are not well explained. So I will consider words mixing
 * alphabetic characters and digits as invalid, as well as multiple "'"
 * inside an alphabetic word:
 * The following will return INVALID_WORD:
 *   P2P
 *   0xFF
 *   A''B
 * The following will return 2 numbers/words:
 *   1'2
 *   A'2
 */

/* get next word in string
 */
static word_t next_word(const char **p)
{
    word_t res={NULL, 0};
    const char *q, *p1=*p;
    static char tmp[1024];
    int pos=0;

    for (; *p1 && !isalpha(*p1) && !isdigit(*p1); ++p1)
        ;

    if (*p1) {
        q=p1;
        /* alphabetic word */
        if (isalpha(*p1)) {
            for (; *q &&(isalpha(*q) || *q=='\''); q++) {
                if (*q=='\'' && *(q-1)=='\'') {   /* two consecutive apostrophes */
                    res.len=INVALID_WORD;
                    goto end;
                }
                tmp[pos++]=tolower(*q);
            }
            if (*(q-1) == '\'')
                q--;
            else if (isdigit(*q)) {               /* digit in word */
                res.len=INVALID_WORD;
                goto end;
            }
        } else {
            for (; *q &&(isdigit(*q)); q++)
                tmp[pos++]=tolower(*q);
            if (isalpha(*q)) {                    /* alphabetic char in number */
                res.len=INVALID_WORD;
                goto end;
            }

        }
        res.word=tmp;
        res.len=q-p1;
        *p=q;
    }
end:
    return res;
}

static int insert_word(word_count_word_t *words, word_t w, int pos)
{
    memcpy(words[pos].text, w.word, w.len);
    words[pos].text[w.len]=0;
    words[pos].count=0;
    return 1;
}

int count_words(const char *sentence, word_count_word_t *words)
{
    word_t w;
    int current=0, new, index;
    hash_t *hash;
    h_entry_t *e;

    hash=h_create(16);
    for (; *sentence;) {
        w=next_word(&sentence);
        if (!w.word)
            break;
        if (w.len > MAX_WORD_LENGTH)
            return EXCESSIVE_LENGTH_WORD;
        if (!(e=h_entry_find(hash, (const unsigned char *)w.word, w.len))) {
            if (current==MAX_WORDS)
                return EXCESSIVE_NUMBER_OF_WORDS;
            insert_word(words, w, current);
            e=h_entry_add(hash, (void *)&words[current], w.len, &new);
            current++;
        }
        index=(word_count_word_t *)e->data-&words[0];
        words[index].count++;
    }
    h_destroy(hash);
    return current;
}

#ifdef UNIT_TEST
static word_count_word_t wtable[MAX_WORDS];

static void reset_wtable()
{
    memset(wtable, 0, sizeof(wtable));
}
static void print_wtable(int n)
{
    for (int i=0; i<n; ++i) {
        printf ("%2d: %2d x \"%s\"\n", i, wtable[i].count, wtable[i].text);
    }

}

int main(int ac, char **av)
{
    int arg=1;
    int res;
    for (; arg<ac; ++arg) {
        reset_wtable();
        res=count_words(av[arg], wtable);
        printf ("res=%d\n", res);
        print_wtable(res);
    }
}
#endif
