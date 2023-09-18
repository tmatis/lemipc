#include <board.h>
#include <strategy.h>
#include <ft_logs.h>
#include <stdlib.h>
#include <stdio.h>
#include <pawn.h>
#include <math.h>
#include <utils_lemipc.h>

#define KILL_ENEMY_BONUS 20
#define KILL_ALLY_MALUS -35
#define CLOSER_TO_ENEMY_BONUS 3
#define CLOSER_TO_ALLY_BONUS 0
#define FARTHER_FROM_ENEMY_MALUS -3
#define FARTHER_FROM_ALLY_MALUS 0
#define BONUS_NOT_MOVING 5

/**
 * @brief Find the closest pawn to the team coord of the team target
 *
 * @param board_instance
 * @param team_target_result
 * @return coord_t coord of the closest pawn
 */
static coord_t choose_target_coord(
    board_instance_t *board_instance,
    team_target_result_t *team_target_result)
{
    double closest_distance = -1;
    coord_t closest_coord = {-1, -1};

    for (int x = 0; x < board_instance->board->board_size; x++)
    {
        for (int y = 0; y < board_instance->board->board_size; y++)
        {
            int *team_id = pawn_get(board_instance, x, y);
            if (*team_id == PLAYER_NO_ID)
                continue;
            if (*team_id == team_target_result->team_id)
            {
                double distance = get_distance(
                    x,
                    y,
                    team_target_result->my_team_coord.x,
                    team_target_result->my_team_coord.y);
                if (closest_distance == -1 || distance < closest_distance)
                {
                    closest_distance = distance;
                    closest_coord.x = x;
                    closest_coord.y = y;
                }
            }
        }
    }
    if (closest_coord.x == -1 && closest_coord.y == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "No target found, this should not happen");
        abort();
    }
    return closest_coord;
}

/**
 * @brief Compute the score of a distance
 * 
 * @param base_distance the distance without moving
 * @param distance the distance with moving
 * @param bonus_per_unit the bonus per unit if we are closer to the target
 * @param malus_per_unit the malus per unit if we are farther from the target
 * @return int the score
 */
static int compute_distance_score(
    double base_distance,
    double distance,
    int bonus_per_unit,
    int malus_per_unit)
{
    double diff = base_distance - distance;
    double abs_diff = fabs(diff);
    // if we are closer to the target, we add a bonus
    if (diff > 0)
        return ceil(abs_diff * bonus_per_unit);
    // if we are farther from the target, we add a malus
    return ceil(abs_diff * malus_per_unit);
}

/**
 * @brief Check if the pawn is going to kill a pawn
 * 
 * @param board_instance the board instance
 * @param x the new x with movement
 * @param y the new y with movement
 * @return bool_t true if the pawn is going to kill a pawn
 */
static bool_t check_is_going_to_kill(
    board_instance_t *board_instance,
    int x,
    int y)
{
    int pawn_around = 0;
    for (int x_around = x - 1; x_around <= x + 1; x_around++)
    {
        for (int y_around = y - 1; y_around <= y + 1; y_around++)
        {
            if (x_around == x && y_around == y)
                continue;
            if (x_around == board_instance->x && y_around == board_instance->y)
                continue;
            if (!is_in_board_bound(x_around, y_around, board_instance->board->board_size))
                continue;
            int *team_id = pawn_get(board_instance, x_around, y_around);
            if (*team_id == PLAYER_NO_ID)
                continue;
            if (*team_id == board_instance->team_id)
            {
                if (pawn_around)
                    return true;
                pawn_around++;
            }
        }
    }
    return false;
}

/**
 * @brief Compute the kill score of a movement
 * 
 * @param board_instance 
 * @param potential_x 
 * @param potential_y 
 * @return int the score
 */
static int compute_kill_score(
    board_instance_t *board_instance,
    int potential_x,
    int potential_y)
{
    int score = 0;
    for (int x = potential_x - 1; x <= potential_x + 1; x++)
    {
        for (int y = potential_y - 1; y <= potential_y + 1; y++)
        {
            if (x == potential_x && y == potential_y)
                continue;
            // if this is the current position, we ignore it
            if (x == board_instance->x && y == board_instance->y)
                continue;
            if (!is_in_board_bound(x, y, board_instance->board->board_size))
                continue;
            int *team_id = pawn_get(board_instance, x, y);
            if (*team_id == PLAYER_NO_ID)
                continue;
            bool_t is_going_to_kill = check_is_going_to_kill(board_instance, x, y);
            // if there is one pawn around this mean if we move here we kill it
            if (is_going_to_kill)
                score += *team_id == board_instance->team_id ? KILL_ALLY_MALUS : KILL_ENEMY_BONUS;
        }
    }
    return score;
}

/**
 * @brief Choose the next movement of the pawn
 *
 * @param board_instance The board instance
 * @return coord_t The coord of the next movement
 */
coord_t strategy_choose_next_move(
    board_instance_t *board_instance,
    team_target_result_t *team_target_result)
{
    coord_t target_coord = choose_target_coord(board_instance, team_target_result);
    int my_team_x = team_target_result->my_team_coord.x;
    int my_team_y = team_target_result->my_team_coord.y;
    int my_coord_x = board_instance->x;
    int my_coord_y = board_instance->y;
    double base_distance_to_target = get_distance(
        my_coord_x,
        my_coord_y,
        target_coord.x,
        target_coord.y);
    double base_distance_to_my_team = get_distance(
        my_coord_x,
        my_coord_y,
        my_team_x,
        my_team_y);
    coord_t best_coord = {-1, -1};
    int best_movement_score = -1000;

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            int potential_x = my_coord_x + x - 1;
            int potential_y = my_coord_y + y - 1;
            if (!is_in_board_bound(potential_x, potential_y, board_instance->board->board_size))
                continue;
            int *team_id = pawn_get(board_instance, potential_x, potential_y);
            if (*team_id != PLAYER_NO_ID)
                continue;
            double distance_to_target = get_distance(
                potential_x,
                potential_y,
                target_coord.x,
                target_coord.y);
            double distance_to_my_team = get_distance(
                potential_x,
                potential_y,
                my_team_x,
                my_team_y);
            int score = 0;
            if (x == 1 && y == 1)
                score += BONUS_NOT_MOVING; // bonus for not moving
            score += compute_distance_score(
                base_distance_to_target,
                distance_to_target,
                CLOSER_TO_ENEMY_BONUS,
                FARTHER_FROM_ENEMY_MALUS);
            score += compute_distance_score(
                base_distance_to_my_team,
                distance_to_my_team,
                CLOSER_TO_ALLY_BONUS,
                FARTHER_FROM_ALLY_MALUS);
            score += compute_kill_score(
                board_instance,
                potential_x,
                potential_y);
            if (score >= best_movement_score)
            {
                best_movement_score = score;
                best_coord.x = potential_x;
                best_coord.y = potential_y;
            }
        }
    }
    return best_coord;
}