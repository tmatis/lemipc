#pragma once

#include <board.h>

/**
 * @brief Lock the game start semaphore
 * 
 * @param board_instance the board instance
 */
void game_start_lock(board_instance_t *board_instance);

/**
 * @brief Unlock the game start semaphore
 * 
 * @param board_instance the board instance
 */
void game_start_unlock(board_instance_t *board_instance);


void game_routine(board_instance_t *board_instance, int required_players);