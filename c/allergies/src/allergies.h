#ifndef ALLERGIES_H
#define ALLERGIES_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
   ALLERGEN_EGGS = 0,
   ALLERGEN_PEANUTS,
   ALLERGEN_SHELLFISH,
   ALLERGEN_STRAWBERRIES,
   ALLERGEN_TOMATOES,
   ALLERGEN_CHOCOLATE,
   ALLERGEN_POLLEN,
   ALLERGEN_CATS,
   ALLERGEN_COUNT,
} allergen_t;

typedef struct {
   int count;
   bool allergens[ALLERGEN_COUNT];
} allergen_list_t;

// We can choose macro or function
#ifdef USE_ALLERGIC_TO_FUNCTION
bool is_allergic_to(const allergen_t allergen, const uint32_t value);
#else
#define is_allergic_to(allerg, val) (!!((val) & (1 << (allerg))))
#endif

allergen_list_t get_allergens(uint32_t value);

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
