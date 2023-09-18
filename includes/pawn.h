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

/**
 * @brief Leave the board and update counters and game state
 * 
 * @param board_instance 
 */
void pawn_leave_board(board_instance_t *board_instance);

/**
 * @brief Return the pawn at the given position
 * 
 * @param board_instance the board instance
 * @param x 
 * @param y 
 * @return int* a pointer to the pawn
 */
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

/**
 * @brief Move a pawn to a new position while checking if the move is valid
 * 
 * @param board_instance
 * @param x 
 * @param y 
 */
void pawn_move(board_instance_t *board_instance, int x, int y);