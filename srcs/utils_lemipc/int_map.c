#include <int_map.h>

/**
 * @brief Compare two int_map by key
 * 
 * @param a
 * @param b 
 * @return int the difference between the two key
 */
static int compare_int_map(int_map_t *a, int_map_t *b)
{
    return a->key - b->key;
}

DEFINE_BTREE_FUNCTIONS(int_map_t, compare_int_map);