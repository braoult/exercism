#ifndef GIGASECOND_H
#define GIGASECOND_H

#include <time.h>

time_t gigasecond_after(time_t);

/* See GNUmakefile in following link for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#ifdef  TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
