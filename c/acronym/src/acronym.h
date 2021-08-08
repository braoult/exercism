#ifndef ACRONYM_H
#define ACRONYM_H

char *abbreviate(const char *phrase);

#ifdef DEBUG
#define ALLOCSIZE  2
#else
#define ALLOCSIZE  1024
#endif

/* See GNUmakefile in following link for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#ifdef  TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
