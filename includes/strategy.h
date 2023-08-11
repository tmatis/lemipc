#pragma once

#include <board.h>

/**
 * @brief Choose a team to target
 *
 * @param board_instance the board instance
 * @return int the team id to target
 */
int strategy_choose_target(board_instance_t *board_instance);