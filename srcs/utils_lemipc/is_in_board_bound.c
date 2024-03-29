#include <bool_t.h>

/**
 * @brief Check if the coord is in the board bound
 * 
 * @param x 
 * @param y 
 * @param board_size 
 * @return bool_t 
 */
bool_t is_in_board_bound(int x, int y, int board_size)
{
    return x >= 0 && x < board_size && y >= 0 && y < board_size;
}