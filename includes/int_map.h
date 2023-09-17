#pragma once

#include <ft_btree.h>

typedef struct {
    int key;
    int value;
} int_map_t;

DEFINE_BTREE_HEADERS(int_map_t);