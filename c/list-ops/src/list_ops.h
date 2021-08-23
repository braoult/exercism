#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef char list_element_t;
typedef struct {
   size_t length;
   list_element_t elements[];
} list_t;

#define MAX_LIST_LENGTH 1024
#define INVALID_LENGTH  (size_t)-1

// constructs a new list
extern list_t *new_list(size_t length, list_element_t elements[]);

// append entries to a list and return the new list
extern list_t *append_list(list_t * list1, list_t * list2);

// filter list returning only values that satisfy the filter function
extern list_t *filter_list(list_t * list, bool(*filter) (list_element_t));

// returns the length of the list
extern size_t length_list(list_t * list);

// return a list of elements whose values equal the list value transformed by
// the mapping function
extern list_t *map_list(list_t * list, list_element_t(*map) (list_element_t));

// folds (reduces) the given list from the left with a function
extern list_element_t foldl_list(list_t * list, list_element_t initial,
                                 list_element_t(*foldl) (list_element_t,
                                                         list_element_t));

// folds (reduces) the given list from the right with a function
extern list_element_t foldr_list(list_t * list, list_element_t initial,
                                 list_element_t(*foldr) (list_element_t,
                                                         list_element_t));

// reverse the elements of the list
extern list_t *reverse_list(list_t * list);

// destroy the entire list
// list will be a dangling pointer after calling this method on it
extern void delete_list(list_t * list);

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
