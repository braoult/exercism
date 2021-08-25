#ifndef PYTHAGOREAN_TRIPLET
#define PYTHAGOREAN_TRIPLET
#include <stdlib.h>
#include <stdint.h>

typedef struct triplet {
    uint16_t a;
    uint16_t b;
    uint16_t c;
} triplet_t;

typedef struct triplets {
    size_t count;
    size_t pool;
    triplet_t *triplets;
} triplets_t;

triplets_t *triplets_with_sum(uint16_t sum);
void free_triplets(triplets_t *triplet);

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

#ifdef  TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
