#ifndef MATCHING_BRACKETS_H
#define MATCHING_BRACKETS_H

#include <stdbool.h>

bool is_paired(const char *input);

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef  TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
