#pragma once

#include <board.h>

#define DEFAULT_SPEED 1
#define SLEEP_TIME 500000

/**
 * @brief Lock the game start semaphore
 * 
 * @param board_instance the board instance
 * @return int 0 on success, non-zero on failure
 */
int game_start_lock(board_instance_t *board_instance);

/**
 * @brief Unlock the game start semaphore
 * 
 * @param board_instance the board instance
 */
void game_start_unlock(board_instance_t *board_instance);

/**
 * @brief check if the game is a draw
 * 
 * @param board_instance 
 * @return bool_t 
 */
bool_t game_check_is_draw(board_instance_t *board_instance);

/**
 * @brief Wait for the required number of players
 * 
 * @param board_instance 
 * @param required_players the number of required players 
 * @return int 0 on success, non-zero on failure
 */
int game_wait_for_players(board_instance_t *board_instance, int required_players);

/**
 * @brief Launch the game routine
 * 
 * @param board_instance the board instance
 * @param required_players the number of required players
 * @param speed the speed of the game
 */
void game_routine(
    board_instance_t *board_instance,
    int required_players,
    int speed);