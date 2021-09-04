#ifndef __BR_COMMON_H
#define __BR_COMMON_H

/* ${LINUX_SRC}/include/linux/compiler_attributes.h, around line 30
 *
 * __has_attribute is supported on gcc >= 5, clang >= 2.9 and icc >= 17.
 * For other compilers, simple implementation (for __falltrough__ only)
 */
#ifndef __has_attribute
#  define __has_attribute(x) __GCC4_has_attribute_##x
#  define __GCC4_has_attribute___assume_aligned__      (__GNUC_MINOR__ >= 9)
#  define __GCC4_has_attribute___copy__                0
#  define __GCC4_has_attribute___designated_init__     0
#  define __GCC4_has_attribute___externally_visible__  1
#  define __GCC4_has_attribute___no_caller_saved_registers__ 0
#  define __GCC4_has_attribute___noclone__             1
#  define __GCC4_has_attribute___nonstring__           0
#  define __GCC4_has_attribute___no_sanitize_address__ (__GNUC_MINOR__ >= 8)
#  define __GCC4_has_attribute___no_sanitize_undefined__ (__GNUC_MINOR__ >= 9)
#  define __GCC4_has_attribute___fallthrough__         0
#  define __GCC4_has_attribute___fallthrough__         0
#endif

/* ${LINUX_SRC}/include/linux/compiler_attributes.h, around line 200
 */
#if __has_attribute(__fallthrough__)
#  define fallthrough                    __attribute__((__fallthrough__))
#else
#  define fallthrough                    do {} while (0);  /* fallthrough */
#endif

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#if defined UNIT_TEST || defined DEBUG
#  include <stdio.h>
#  include <stdlib.h>
#endif

#ifdef  TESTALL
#  undef  TEST_IGNORE
#  define TEST_IGNORE() {}
#endif

#endif  /* __BR_COMMON_H */
