#pragma once

#include <bool_t.h>

/**
 * @brief Check if the coord is in the board bound
 * 
 * @param x 
 * @param y 
 * @param board_size 
 * @return bool_t 
 */
bool_t is_in_board_bound(int x, int y, int board_size);

/**
 * @brief Set the force stop flag
*/
void force_stop(void);

/**
 * @brief Check if the force stop flag is set
 * 
 * @return bool_t
 */
bool_t force_stop_is_set(void);