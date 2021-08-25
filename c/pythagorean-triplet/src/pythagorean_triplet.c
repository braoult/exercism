#include <malloc.h>

#include "pythagorean_triplet.h"

#define POOL_SIZE 10

/* V1: initial version
 * V2: cormetic changes
 * V3: add pool for realloc instead of single realloc
 */
void free_triplets(triplets_t *t)
{
    free(t->triplets);
    free(t);
}

static triplets_t *new_triplet()
{
    triplets_t *t=malloc(sizeof(triplets_t));
    if (t) {
        t->count = 0;
        t->pool  = 0;
        t->triplets = NULL;
    }
    return t;
}

static triplets_t *add_triplet(triplets_t *t, const uint16_t a, const uint16_t b,
                               const uint16_t c)
{
    /* we may directly call add_triplet() without new_triplet. Not used here,
     * but could be useful if triplets_with_sum() would return NULL when no
     * solution found.
     */
    if (! (t || (t = new_triplet())))
        return NULL;

    if (t->count == t->pool) {
        t->pool += POOL_SIZE;
        if (!(t->triplets = realloc(t->triplets, sizeof(triplets_t) +
                                    t->pool * sizeof(triplet_t)))) {
            free(t);
            return NULL;
        }
    }
    t->triplets[t->count] = (triplet_t) {a, b, c};
    t->count++;
    return t;
}

/* algorithm from : https://stackoverflow.com/a/2818750/3079831
 */
triplets_t *triplets_with_sum(uint16_t sum)
{
    int a, b, c;
    triplets_t *t;

    if (!(t = new_triplet()))
        return NULL;
    if (sum%2)
        return t;

    for (a = 1; a <= sum/3; a++) {
        for (b = a + 1; b <= sum/2; b++) {
            c = sum - a - b;
            if (a*a + b*b == c*c)
                if (!(t = add_triplet(t, a, b, c)))
                    return NULL;
        }
    }
    return t;
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    resistor_band_t i[2];

    for (; arg<ac-1; ++arg, ++arg) {
        *i=atoi(av[arg]);
        *(i+1)=atoi(av[arg+1]);
        printf("color(%d, %d)=%d\n", i[0], i[1], color_code(i));
    }
}
#endif
