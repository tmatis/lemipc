#include <int_map.h>

static int compare_int_map(int_map_t *a, int_map_t *b)
{
    return a->key - b->key;
}

DEFINE_BTREE_FUNCTIONS(int_map_t, compare_int_map);