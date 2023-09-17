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
int *pawn_get(board_instance_t *board_instance, int x, int y);

/**
 * @brief Return the number of pawns of a team
 * 
 * @param board_instance the board instance
 * @param team_id the team id
 * @return int the number of pawns of a team
 */
int pawn_count_team_player(board_instance_t *board_instance, int team_id);

/**
 * @brief Check if the pawn is dead
 * 
 * @param board_instance the board instance
 * @return bool_t true if the pawn is dead, false otherwise 
 */
bool_t pawn_is_dead(board_instance_t *board_instance);

void pawn_move(board_instance_t *board_instance, int x, int y);