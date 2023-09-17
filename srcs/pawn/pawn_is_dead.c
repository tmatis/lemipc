#include <pawn.h>
#include <int_map.h>
#include <utils.h>

/**
 * @brief Check if the pawn is dead
 * 
 * @param board_instance the board instance
 * @return bool_t true if the pawn is dead, false otherwise 
 */
bool_t pawn_is_dead(board_instance_t *board_instance)
{
    /*
    ** key: team_id
    ** value: number of pawn around
    */
    btree_int_map_t *root = NULL;
    for (int x = board_instance->x - 1; x <= board_instance->x + 1; x++)
    {
        for (int y = board_instance->y - 1; y <= board_instance->y + 1; y++)
        {
            if (x == board_instance->x && y == board_instance->y)
                continue;
            if (!is_in_board_bound(x, y, board_instance->board->board_size))
                continue;
            int *team_id = pawn_get(board_instance, x, y);
            if (*team_id == PLAYER_NO_ID)
                continue;
            int_map_t int_map = {
                .key = *team_id,
                .value = 1};
            btree_int_map_t *node = btree_int_map_t_search(root, &int_map);
            if (!node)
                btree_int_map_t_insert(&root, &int_map);
            else
            {
                btree_int_map_t_clear(&root, NULL);
                return true;
            }
        }
    }
    btree_int_map_t_clear(&root, NULL);
    return false;
}