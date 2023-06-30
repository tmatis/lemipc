#include <board.h>
#include <sys/sem.h>
#include <ft_logs.h>
#include <ft_string.h>
#include <stdlib.h>
#include <errno.h>


void board_lock(board_instance_t *board_instance)
{
    struct sembuf lock_op = {
        .sem_num = 0,
        .sem_op = -1,
        .sem_flg = 0
    };
    if (semop(board_instance->sem_id, &lock_op, 1) == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "board_lock",
            "could not lock semaphore " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            board_instance->sem_id,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void board_unlock(board_instance_t *board_instance)
{
    struct sembuf unlock_op = {
        .sem_num = 0,
        .sem_op = 1,
        .sem_flg = 0
    };
    if (semop(board_instance->sem_id, &unlock_op, 1) == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "board_unlock",
            "could not unlock semaphore " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            board_instance->sem_id,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
}