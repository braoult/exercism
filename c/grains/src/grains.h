#ifndef GRAINS_H
#define GRAINS_H

#include <stdint.h>

extern uint64_t square(uint8_t index);
extern uint64_t total(void);

/* See GNUmakefile in following link for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#ifdef  TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
