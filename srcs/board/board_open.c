#include <board.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <ft_string.h>
#include <ft_logs.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/msg.h>

board_instance_t *board_open(key_t key, int slot_count)
{
    size_t board_size = board_compute_size(slot_count);
    int shm_id = shmget(key, board_size, 0);
    if (shm_id == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "board_open",
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
            "board_open",
            "could not attach shared memory segment " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            key,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (board->board_size != slot_count)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "board_open",
            "board size mismatch: expected " C_BOLD "(" C_YELLOW "%zu" C_RESET "), got " C_BOLD "(" C_YELLOW "%d" C_RESET ")",
            slot_count,
            board->board_size);
        exit(EXIT_FAILURE);
    }
    board_instance_t *board_instance = malloc(sizeof(board_instance_t));
    if (board_instance == NULL)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "board_open",
            "could not allocate memory for board instance: %s",
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    board_instance->board = board;
    board_instance->sem_id = semget(key, 1, 0);
    board_instance->msg_id = msgget(key, 0);
    board_instance->shm_id = shm_id;
    if (board_instance->sem_id == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "board_open",
            "could not get semaphore " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            key,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    return (board_instance);
}