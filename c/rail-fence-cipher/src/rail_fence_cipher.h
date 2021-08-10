#ifndef RAIL_FENCE_CIPHER_H
#define RAIL_FENCE_CIPHER_H

#include <stddef.h>

#define ENCODE 0
#define DECODE 1

char *doit(char *text, size_t rails, int action);

#define encode(t, r) doit(t, r, ENCODE)
#define decode(t, r) doit(t, r, DECODE)

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef  TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
