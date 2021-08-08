#include <string.h>
#include <malloc.h>

#include "hash.h"

#define HASH_SIZE 50

//static hash_t *hash_table[HASH_SIZE];
static h_entry_t *pool_free, *alloc_entries;
static int n_entries;

void h_init(hash_t *hash)
{
    memset(hash->entries, 0, sizeof(h_entry_t)*hash->size);
}

hash_t *h_create(int size)
{
    hash_t *hash;

    if ( !(hash=calloc(sizeof(hash_t) + size*(sizeof (h_entry_t *)), 1)) )
        return NULL;
    hash->size=size;
    return hash;
}

void h_destroy(hash_t *h)
{
    h_entry_t *tmp;

    for (int i=0; i<h->size; ++i) {
        while (h->entries[i]) {
            tmp=h->entries[i]->next;
            h_entry_free(h->entries[i]);
            h->entries[i]=tmp;
        }
    }
    free(h);
}

/*  Daniel J. Bernstein's djb2 hash function */
unsigned long hash_djb2(const unsigned char *str, const int len)
{
    unsigned long hash = 5381;

    for (int i=0; i<len; ++i)
        hash = ((hash << 5) + hash) + str[i]; /* hash * 33 + str[i] */
    return hash;
}

void h_entry_free(h_entry_t *e)
{
    e->next=pool_free;
    pool_free=e;
}

h_entry_t *h_entry_find(hash_t *h, const unsigned char *s, const int l)
{
    unsigned long hash=hash_djb2(s, l);
    h_entry_t *entry;
    int found=0;

#   ifdef DEBUG
    printf("h_entry_find([%.*s]): hash=%#lx (%lu) - ", l, s, hash, hash%h->size);
#   endif
    hash%=h->size;
    for (entry=h->entries[hash]; entry; entry=entry->next) {
        if (l == entry->key_len && !memcmp(entry->data, s, l)) {
            found=1;
            break;
        }
    }
#   ifdef DEBUG
    printf("ret=%p\n", found? (void *)entry: (void *)-1);
#   endif
    return found? entry: NULL;
}

h_entry_t *h_entry_add(hash_t *h, const unsigned char *s, const int l, int *insert)
{
    unsigned long hash;
    h_entry_t *entry;

    *insert=0;

    if (!pool_free) {
        register int i=n_entries;

        n_entries+=ENTRY_ALLOC_SIZE;
#       ifdef DEBUG
        printf("get_hash: allocating %d new entries - total entries=%d\n",
               ENTRY_ALLOC_SIZE, n_entries);
#       endif
        alloc_entries=reallocarray(alloc_entries, n_entries, sizeof(h_entry_t));

        for (; i<n_entries; ++i) {                /* create free entries list */
            (alloc_entries+i)->next=pool_free;
            pool_free=alloc_entries+i;
        }
    }
    if ((entry=h_entry_find(h, s, l)))
        return entry;

    *insert=1;

    hash=hash_djb2(s, l)%h->size;

    /* get a free entry from pool */
    entry=pool_free;
    pool_free=pool_free->next;

    /* set entry in hash */
    entry->next=h->entries[hash];
    h->entries[hash]=entry;

    entry->data=(unsigned char *)s;
    entry->key_len=l;

    //assert(entry!=freenodes);
#   ifdef DEBUG
    printf("h_entry_add: %p\n", (void *)entry);
#   endif
    return entry;
}
