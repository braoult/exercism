#include <malloc.h>
#include <string.h>
#include <stdint.h>

#include "list_ops.h"

#define SIZE(l) ((l)->length * sizeof(list_element_t))

list_t *new_list(size_t len, list_element_t elts[])
{
    list_t *list;

    if (len > MAX_LIST_LENGTH ||
        !(list=malloc(sizeof(list_t) + len*sizeof(list_element_t))))
        return NULL;
    list->length = len;
    if (elts)
        memcpy(list->elements, elts, len * sizeof(list_element_t));
    return list;
}

list_t *append_list(list_t *l1, list_t *l2)
{
    list_t *l;
    size_t len=l1->length+l2->length;

    if (!(l=new_list(len, NULL)))
        return NULL;
    memcpy(l->elements, l1->elements, l1->length * sizeof(list_element_t));
    memcpy(l->elements + l1->length, l2->elements,
           l2->length * sizeof(list_element_t));
    l->length=len;
    return l;
}

list_t *filter_list(list_t * l, bool(*f) (list_element_t))
{
    size_t p1, p2;
    list_t *list=new_list(l->length, NULL);

    if (list) {
        for (p1=0, p2=0; p1 < l->length; ++p1) {
            if (f(l->elements[p1]))
                list->elements[p2++]=l->elements[p1];
        }
    }
    list->length=p2;
    return list;
}

/* I don't like this function return value, and more generally using size_t
 * as list length.
 */
size_t length_list(list_t *l)
{
    return l? l->length: INVALID_LENGTH;
}

list_t *map_list(list_t * l, list_element_t(*map) (list_element_t))
{
    size_t i;
    list_t *list=new_list(l->length, NULL);

    if (list) {
        for (i=0; i < l->length; ++i)
            list->elements[i] = map(l->elements[i]);
    }
    return list;
}

list_element_t foldl_list(list_t * l, list_element_t init,
                          list_element_t(*f) (list_element_t, list_element_t))
{
    size_t i;

    for (i = 0; i < l->length; ++i)
        init = f(l->elements[i], init);
    return init;
}

list_element_t foldr_list(list_t * l, list_element_t init,
                          list_element_t(*f) (list_element_t, list_element_t))
{
    ptrdiff_t i;

    for (i = l->length-1; i >= 0; --i)
        init = f(l->elements[i], init);
    return init;
}

list_t *reverse_list(list_t * l)
{
    size_t i;
    list_t *list=new_list(l->length, NULL);

    if (list) {
        for (i=0; i < l->length; ++i)
            list->elements[l->length-i-1] = l->elements[i];
    }
    return list;
}

void delete_list(list_t * l)
{
    free(l);
}


/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
static void print_list(list_t *l)
{
    printf("list (%lu) = ", l->length);
    for (size_t i=0; i<l->length; ++i)
        printf("%d ", l->elements[i]);
    printf("\n");
}

int main(int ac, char **av)
{
    int arg=1, i;
    list_t *l1=new_list(0, NULL);
    list_t *l2, *l3;

    for (; arg<ac; ++arg) {
        i=atoi(av[arg]);
        l2 = new_list(1, (list_element_t[]){ i });
        l3 = append_list(l1, l2);
        delete_list(l2);
        delete_list(l1);
        l1=l3;
    }
    print_list(l1);
    delete_list(l1);
}
#endif
