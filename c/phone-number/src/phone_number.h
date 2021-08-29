#ifndef PHONE_NUMBER_H
#define PHONE_NUMBER_H

#define NUMBER_LENGTH 10

char *phone_number_clean(const char *input);

/* from :
 * https://github.com/torvalds/linux/blob/master/include/linux/compiler_attributes.h
 * around line 200
 * should work with recent gcc/clang
 */
#if __has_attribute(__fallthrough__)
# define fallthrough                    __attribute__((__fallthrough__))
#else
# define fallthrough                    do {} while (0)  /* fallthrough */
#endif

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
