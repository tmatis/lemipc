#include <board.h>
#include <ft_logs.h>
#include <errno.h>
#include <stdlib.h>
#include <ft_string.h>

/**
 * @brief Lock the game start semaphore
 * 
 * @param board_instance the board instance
 */
void game_start_lock(board_instance_t *board_instance)
{
    struct sembuf lock_op = {
        .sem_num = 1,
        .sem_op = -1,
        .sem_flg = 0
    };
    if (semop(board_instance->sem_id, &lock_op, 1) == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "game_start_lock",
            "could not lock semaphore " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            board_instance->sem_id,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Unlock the game start semaphore
 * 
 * @param board_instance the board instance
 */
void game_start_unlock(board_instance_t *board_instance)
{
    struct sembuf unlock_op = {
        .sem_num = 1,
        .sem_op = 1,
        .sem_flg = 0
    };
    if (semop(board_instance->sem_id, &unlock_op, 1) == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "game_start_unlock",
            "could not unlock semaphore " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            board_instance->sem_id,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
}