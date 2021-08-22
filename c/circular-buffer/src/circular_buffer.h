#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdlib.h>

typedef char buffer_value_t;

/* used and tail are redundant, but allow easier code (and maybe easier
 * to read ?).
 */
typedef struct circular_buffer {
    int head;
    int tail;
    int used;
    int size;
    buffer_value_t *buf;
} circular_buffer_t;

extern circular_buffer_t *new_circular_buffer(size_t size);
extern int do_write(circular_buffer_t *buffer, buffer_value_t value, int force);
extern int read(circular_buffer_t *buffer, buffer_value_t *retval);
extern int clear_buffer(circular_buffer_t *buffer);
extern void delete_buffer(circular_buffer_t *buffer);

#define write(buffer, value)     do_write((buffer), (value), 0)
#define overwrite(buffer, value) do_write((buffer), (value), 1)

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
