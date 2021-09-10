#include "run_length_encoding.h"
/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1, what;
    char *res;

    what = *av[arg++];                            /* 'e', 'd' */
    for (; arg<ac; ++arg) {
        switch (what) {
            case 'e':
                printf("enc[%s]=%d [%s]\n", av[arg], encode_len(av[arg]),
                       res=encode(av[arg]));
                printf("dec[%s]=%d [%s]\n", res, decode_len(res), decode(res));
                break;
            case 'd':
                printf("dec[%s]=%d [%s]\n", av[arg], encode_len(av[arg]),
                       res=decode(av[arg]));
                printf("enc[%s]=%d [%s]\n", res, decode_len(res), decode(res));
        }
    }
}
#endif
