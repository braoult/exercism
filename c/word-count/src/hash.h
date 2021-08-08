#ifndef _HASH_H
#define _HASH_H

#include <stdbool.h>

typedef struct h_entry {
    void *data;
    int key_len;
    struct h_entry *prev, *next;
} h_entry_t;

typedef struct {
    int size;
    h_entry_t *entries[];
} hash_t;

/* a few predefined hash sizes */
typedef struct {
    int size;
    h_entry_t *entries[16];
} hash_16_t;

typedef struct {
    int size;
    h_entry_t *entries[128];
} hash_128_t;

typedef struct {
    int size;
    h_entry_t *entries[1024];
} hash_1024_t;

#define ENTRY_ALLOC_SIZE 20

/* hash map functions */
hash_t *h_create(int size);
void h_init(hash_t *);
void h_destroy(hash_t *);

/* static free_nodes */
void set_pool_free_static(h_entry_t *p);

/* hash entries functions */
h_entry_t *h_entry_add(hash_t *, const unsigned char *, const int, int *);
h_entry_t *h_entry_find(hash_t *, const unsigned char *, const int);
void h_entry_free(h_entry_t *);


/* hash function */
unsigned long hash_djb2(const unsigned char *str, const int len);

#endif
