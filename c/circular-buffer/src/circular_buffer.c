#include <malloc.h>
#include <errno.h>

#include "circular_buffer.h"

#define INC(v, size) {if (++v==size) v=0;}

circular_buffer_t *new_circular_buffer(size_t size)
{
    circular_buffer_t *head = NULL;

    if (size > 0) {
        if ((head=malloc(sizeof(*head)))) {
            clear_buffer(head);
            head->size = size;
            /* we could have only 1 alloc, I just prefer this double alloc
             */
            if (!(head->buf  = calloc(size, sizeof(buffer_value_t)))) {
                free(head);
                head = NULL;
            }
        }
    }
    return head;
}

int do_write(circular_buffer_t *b, buffer_value_t v, int f)
{
    if (!f  && b->used == b->size) {
        errno = ENOBUFS;
        return EXIT_FAILURE;
    }
    b->buf[b->head] = v;
    INC(b->head, b->size);
    if (f && b->used == b->size)                  /* overwrite and full */
        INC(b->tail, b->size);
    if (b->used < b->size)                        /* normal write */
        b->used++;
    return EXIT_SUCCESS;
}

int read(circular_buffer_t *b, buffer_value_t *p)
{
    if (!b->used) {
        errno = ENODATA;
        return EXIT_FAILURE;
    }
    b->used--;
    *p = b->buf[b->tail];
    INC(b->tail, b->size);
    return EXIT_SUCCESS;
}

int clear_buffer(circular_buffer_t *b)
{
    b->head = 0;
    b->tail = 0;
    b->used = 0;
    return EXIT_SUCCESS;
}

void delete_buffer(circular_buffer_t *b) {
    free(b->buf);
    free(b);
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    /* not done for circular buffer : simple exercise, with difficult testing */
}
#endif
