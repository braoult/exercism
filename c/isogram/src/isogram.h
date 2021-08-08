#ifndef ISOGRAM_H
#define ISOGRAM_H

#include <stdbool.h>

bool is_isogram(const char phrase[]);

#ifdef TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
