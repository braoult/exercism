#include <malloc.h>

#include "br-list.h"
#include "linked_list.h"

struct list_node {
    ll_data_t data;
    struct list_head list;
};

/* duplicate of list_head struct
 */
struct list {
    struct list_head *next, *prev;
};

/* constructs a new (empty) list
 */
struct list *list_create()
{
    struct list_head *list;

    if (!(list=malloc(sizeof (*list))))
        return NULL;
    INIT_LIST_HEAD(list);
    return (struct list *) list;
}

/* counts the items on a list
 */
size_t list_count(const struct list *list_head)
{
    size_t len = 0;
    struct list_head *p;

    list_for_each(p, (struct list_head *)list_head)
        len++;
    return len;
}

/* inserts item at back of a list
 */
void list_push(struct list *list, ll_data_t item_data)
{
    struct list_node *p;

    if ((p=malloc(sizeof(*p)))) {
        p->data = item_data;
        list_add_tail(&p->list, (struct list_head*)list);
    }
}

/* deletes an element
 */
static ll_data_t _list_del(struct list_head *list)
{
    struct list_node *node;
    ll_data_t data;

    node = list_entry(list, struct list_node, list);
    data = node->data;
    list_del(&node->list);
    free(node);
    return data;
}

/* removes item from back of a list
 */
ll_data_t list_pop(struct list *list)
{
    return list_empty((struct list_head*)list) ? -1 : _list_del(list->prev);
}

/* inserts item at front of a list
 */
void list_unshift(struct list *list, ll_data_t item_data)
{
    struct list_node *p;

    if ((p=malloc(sizeof(*p)))) {
        p->data = item_data;
        list_add(&p->list, (struct list_head*)list);
    }
}

/* removes item from front of a list
 */
ll_data_t list_shift(struct list *list)
{
    return list_empty((struct list_head*)list) ? -1 : _list_del(list->next);
}

/* finds a element that matches data
 */
static struct list_node *_node_find(struct list *list, ll_data_t data)
{
    struct list_node *p;

    list_for_each_entry(p, (struct list_head *)list, list) {
        if (p->data == data)
            return p;
    }
    return NULL;
}

/* deletes a node that holds the matching data
 */
void list_delete(struct list *list, ll_data_t data)
{
    struct list_node *p;

    if ((p = _node_find(list, data)))
        _list_del(&p->list);
}

/* destroys an entire list
 * list will be a dangling pointer after calling this method on it
 */
void list_destroy(struct list *list)
{
    struct list_head *cur, *tmp;

    list_for_each_safe(cur, tmp, (struct list_head *)list)
        _list_del(cur);
    free(list);
}
