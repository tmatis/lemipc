#include <board.h>
#include <ft_logs.h>
#include <unistd.h>
#include <stdlib.h>
#include <ft_string.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/msg.h>

void board_disconnect(board_instance_t *board_instance)
{
    board_lock(board_instance);
    board_instance->board->clients_connected--;
    if (board_instance->board->clients_connected == 0)
    {
        ft_log(
            LOG_LEVEL_INFO,
            "last client disconnected, removing board");
        if (shmdt(board_instance->board) == -1)
        {
            ft_log(
                LOG_LEVEL_ERROR,
                "could not detach shared memory segment " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
                board_instance->board,
                ft_strerror(errno));
        }
        if (shmctl(board_instance->shm_id, IPC_RMID, NULL) == -1)
        {
            ft_log(
                LOG_LEVEL_ERROR,
                "could not remove shared memory segment " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
                board_instance->board,
                ft_strerror(errno));
        }
        if (semctl(board_instance->sem_id, 0, IPC_RMID) == -1)
        {
            ft_log(
                LOG_LEVEL_ERROR,
                "could not remove semaphore " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
                board_instance->sem_id,
                ft_strerror(errno));
        }
        if (msgctl(board_instance->msg_id, IPC_RMID, NULL) == -1)
        {
            ft_log(
                LOG_LEVEL_ERROR,
                "could not remove message queue " C_BOLD "(" C_YELLOW "%#x" C_RESET "): %s",
                board_instance->msg_id,
                ft_strerror(errno));
        }
    }
    else
    {
        ft_log(
            LOG_LEVEL_INFO,
            "client disconnected, %d clients remaining",
            board_instance->board->clients_connected);
        board_unlock(board_instance);
    }
    free(board_instance);
}