#pragma once

#include <board.h>
#include <bool_t.h>

/**
 * @brief Return true if the pawn has not been placed, false otherwise
 *
 * @param board_instance The board instance
 * @return bool_t true if the pawn has not been placed, false otherwise
 */
bool_t pawn_join_board(board_instance_t *board_instance);
void pawn_leave_board(board_instance_t *board_instance);
player_t *pawn_get(board_instance_t *board_instance, int x, int y);