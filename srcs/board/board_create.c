#include <board.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <ft_string.h>
#include <ft_logs.h>
#include <stdlib.h>
#include <errno.h>
#include <ft_printf.h>
#include <sys/msg.h>
#include <game.h>

board_instance_t *board_create(key_t key, int slot_count)
{
    size_t board_size = board_compute_size(slot_count);
    int shm_id = shmget(key, board_size, IPC_CREAT | IPC_EXCL | 0644);
    if (shm_id == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "could not create shared memory segment " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            key,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    board_t *board = shmat(shm_id, NULL, 0);
    if (board == (void *)-1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "could not attach shared memory segment " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            key,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    board->board_size = slot_count;
    board->game_state = GAME_IDLE;
    board->game_result = NO_RESULT;
    board_instance_t *board_instance = malloc(sizeof(board_instance_t));
    if (board_instance == NULL)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "could not allocate memory for board instance: %s",
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    board_instance->board = board;
    board_instance->sem_id = semget(key, 2, IPC_CREAT | IPC_EXCL | 0644);
    board_instance->msg_id = msgget(key, IPC_CREAT | IPC_EXCL | 0644);
    board_instance->shm_id = shm_id;
    if (board_instance->sem_id == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "could not create semaphore " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            key,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (semctl(board_instance->sem_id, 0, SETVAL, 0) == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "could not set semaphore value " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            key,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (semctl(board_instance->sem_id, 1, SETVAL, 0) == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "could not set semaphore value " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
            key,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }

    board_instance->board->clients_connected = 0;
    board_instance->board->players_on_board = 0;
    for (int i = 0; i < slot_count * slot_count; i++)
        board_instance->board->slots[i] = EMPTY_CELL;
    game_start_unlock(board_instance);
    return (board_instance);
}