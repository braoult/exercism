#ifndef HAMMING_H
#define HAMMING_H

int compute(const char *lhs, const char *rhs);

/* Note: For explanation on section below, see 'GNUfilename' included in
 * link below :
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#ifdef  TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
