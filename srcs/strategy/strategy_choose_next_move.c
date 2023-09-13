#include <board.h>
#include <strategy.h>
#include <ft_logs.h>
#include <stdlib.h>
#include <pawn.h>

#define KILL_ENEMY_BONUS 20
#define KILL_ALLY_MALUS -35
#define CLOSER_TO_ENEMY_BONUS 3
#define CLOSER_TO_ALLY_BONUS -1
#define FARTHER_FROM_ENEMY_MALUS -3
#define FARTHER_FROM_ALLY_MALUS 0

/**
 * @brief Find the closest pawn to the team coord of the team target
 *
 * @param board_instance
 * @param team_target_result
 * @return coord_t coord of the closest pawn
 */
coord_t choose_target_coord(
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
            "choose_target_coord",
            "No target found, this should not happen");
        exit(EXIT_FAILURE);
    }
    return closest_coord;
}

bool_t is_in_board_bound(int x, int y, int board_size)
{
    return x >= 0 && x < board_size && y >= 0 && y < board_size;
}

int compute_distance_score(
    double base_distance,
    double distance,
    int bonus_per_unit,
    int malus_per_unit)
{
    int diff = base_distance - distance;
    int abs_diff = abs(diff);
    // if we are closer to the target, we add a bonus
    if (diff > 0)
        return abs_diff * bonus_per_unit;
    // if we are farther from the target, we add a malus
    return abs_diff * malus_per_unit;
}

// int compute_kill_score(
//     board_instance_t *board_instance,
//     int x,
//     int y,
//     int my_team_id)
// {

// }

/**
 * @brief Choose the next movement of the pawn
 *
 * @param board_instance The board instance
 * @return int The direction to move
 */
coord_t strategy_choose_next_move(
    board_instance_t *board_instance,
    team_target_result_t *team_target_result)
{
    int possible_movement[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    coord_t target_coord = choose_target_coord(board_instance, team_target_result);
    int target_x = target_coord.x;
    int target_y = target_coord.y;
    int my_team_x = team_target_result->my_team_coord.x;
    int my_team_y = team_target_result->my_team_coord.y;
    int my_coord_x = board_instance->x;
    int my_coord_y = board_instance->y;
    double base_distance_to_target = get_distance(my_coord_x, my_coord_y, target_x, target_y);
    double base_distance_to_my_team = get_distance(my_coord_x, my_coord_y, my_team_x, my_team_y);

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
            double distance_to_target = get_distance(potential_x, potential_y, target_x, target_y);
            double distance_to_my_team = get_distance(potential_x, potential_y, my_team_x, my_team_y);
            possible_movement[x][y] += compute_distance_score(
                base_distance_to_target,
                distance_to_target,
                CLOSER_TO_ENEMY_BONUS,
                FARTHER_FROM_ENEMY_MALUS);
            possible_movement[x][y] += compute_distance_score(
                base_distance_to_my_team,
                distance_to_my_team,
                CLOSER_TO_ALLY_BONUS,
                FARTHER_FROM_ALLY_MALUS);
        }
    }

    int max_score = -1000;
    coord_t best_coord = {-1, -1};
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            int score = possible_movement[x][y];
            if (score > max_score)
            {
                max_score = score;
                best_coord.x = my_coord_x + x - 1;
                best_coord.y = my_coord_y + y - 1;
            }
        }
    }
    return best_coord;
}