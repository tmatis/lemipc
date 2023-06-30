#include <board.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <ft_string.h>
#include <ft_logs.h>
#include <stdlib.h>
#include <errno.h>


board_instance_t *board_open(key_t key)
{
    int shm_id = shmget(key, sizeof(board_t), 0);
    if (shm_id == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "open_board",
            "could not get shared memory segment " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            key,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    board_t *board = shmat(shm_id, NULL, 0);
    if (board == (void *)-1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "open_board",
            "could not attach shared memory segment " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            key,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    board_instance_t *board_instance = malloc(sizeof(board_instance_t));
    if (board_instance == NULL)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "open_board",
            "could not allocate memory for board instance: %s",
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    board_instance->board = board;
    board_instance->sem_id = semget(key, 1, 0);
    if (board_instance->sem_id == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "open_board",
            "could not get semaphore " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            key,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    return (board_instance);
}