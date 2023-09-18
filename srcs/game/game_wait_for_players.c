#include <ft_logs.h>
#include <game.h>
#include <utils_lemipc.h>
#include <unistd.h>

/**
 * @brief Check if the game can start
 * 
 * @param board_instance 
 * @param required_players the number of required players
 * @return bool_t 
 */
static bool_t can_start(board_instance_t *board_instance, int required_players)
{
    board_lock(board_instance);
    if (board_instance->board->game_state == GAME_RUNNING)
    {
        board_unlock(board_instance);
        return true;
    }
    board_instance->board->game_result = NO_RESULT;
    if (board_instance->board->players_on_board >= required_players)
    {
        board_instance->board->game_state = GAME_RUNNING;
        board_unlock(board_instance);
        return true;
    }
    board_unlock(board_instance);
    return false;
}

/**
 * @brief Wait for the required number of players and control semaphore
 * 
 * @param board_instance 
 * @param required_players the number of required players 
 * @return int 0 on success, non-zero on failure
 */
int game_wait_for_players(board_instance_t *board_instance, int required_players)
{
    ft_log(
        LOG_LEVEL_INFO,
        "waiting for %d players",
        required_players);
    if (game_start_lock(board_instance))
        return (1);
    ft_log(
        LOG_LEVEL_INFO,
        "game start semaphore locked");
    while (!can_start(board_instance, required_players))
    {
        usleep(100000);
        if (force_stop_is_set())
        {
            ft_log(
                LOG_LEVEL_WARNING,
                "forced stop while waiting for players");
            game_start_unlock(board_instance);
            return (1);
        }
    }
    ft_log(
        LOG_LEVEL_INFO,
        "game start semaphore unlocked");
    game_start_unlock(board_instance);
    return (0);
}