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
 * @return int The direction to move
 */
coord_t strategy_choose_next_move(
    board_instance_t *board_instance,
    team_target_result_t *team_target_result);