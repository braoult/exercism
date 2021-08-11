#ifndef MEETUP_H
#define MEETUP_H

int meetup_day_of_month(unsigned int year, unsigned int month, const char *week,
                        const char *day_of_week);

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
