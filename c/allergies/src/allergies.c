#include "allergies.h"

bool is_allergic_to(const allergen_t all, const uint32_t val)
{
    return !!(val & (1 << all));
}

allergen_list_t get_allergens(uint32_t val)
{
    allergen_list_t list = { .count = 0 };
    allergen_t i;

    for (i=0; i<ALLERGEN_COUNT; ++i) {
        list.allergens[i] = is_allergic_to(i, val);
        list.count += list.allergens[i];
    }
    return list;
}
