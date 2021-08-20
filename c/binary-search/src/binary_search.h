#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <stddef.h>

const int *binary_search(int value, const int *arr, size_t length);

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
