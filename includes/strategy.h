#pragma once

#include <board.h>

typedef struct
{
    int x;
    int y;
} coord_t;

typedef struct
{
    int team_id;
    coord_t my_team_coord;
} team_target_result_t;

/**
 * @brief Get the distance between two points
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 * @return double 
 */
double get_distance(int x1, int y1, int x2, int y2);
/**
 * @brief Choose a team to target
 *
 * @param board_instance the board instance
 * @return the team id to target and the coord of my team
 */
team_target_result_t strategy_choose_team_target(board_instance_t *board_instance);


/**
 * @brief Choose the next movement of the pawn
 *
 * @param board_instance The board instance
 * @return coord_t The coord of the next movement
 */
coord_t strategy_choose_next_move(
    board_instance_t *board_instance,
    team_target_result_t *team_target_result);