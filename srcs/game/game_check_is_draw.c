#include <int_map.h>
#include <game.h>

/**
 * @brief check if the game is a draw
 * 
 * @param board_instance 
 * @return bool_t 
 */
bool_t game_check_is_draw(board_instance_t *board_instance)
{
    btree_int_map_t *root = NULL;
    int board_size = board_instance->board->board_size;
    for (int i = 0; i < board_size * board_size; i++)
    {
        int slot = board_instance->board->slots[i];
        if (slot == EMPTY_CELL)
            continue;
        int_map_t int_map = {slot, 1};
        btree_int_map_t *node = btree_int_map_t_search(root, &int_map);
        if (node == NULL)
            btree_int_map_t_insert(&root, &int_map);
        else
        {
            btree_int_map_t_clear(&root, NULL);
            return false;
        }
    }
    btree_int_map_t_clear(&root, NULL);
    return true;
}