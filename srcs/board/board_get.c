#include <board.h>
#include <ft_logs.h>
#include <ft_string.h>
#include <bool_t.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void touch(const char *path)
{
    int fd = open(path, O_CREAT, 0644);
    if (fd == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "could not create/open file " C_BOLD "(" C_YELLOW "%s" C_RESET "): %s",
            path,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    close(fd);
}

board_instance_t *board_get(bool_t allow_creation, int slot_count)
{
    touch(IPC_PATH);
    key_t key = ftok(IPC_PATH, IPC_KEY);
    if (key == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "could not get key " C_BOLD "(" IPC_PATH ":%#x)" C_RESET ": %s",
            IPC_KEY,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    board_instance_t *board_instance;
    int sem_id = semget(key, 2, 0);
    if (sem_id == -1 && !allow_creation)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "Board does not exist, and creation is not allowed");
        exit(EXIT_FAILURE);
    }
    else if (sem_id == -1)
    {
        ft_log(
            LOG_LEVEL_INFO,
            "Board does not exist, creating it...");
        board_instance = board_create(key, slot_count);
    }
    else
    {
        ft_log(
            LOG_LEVEL_INFO,
            "Board exists, opening it...");
        board_instance = board_open(key, slot_count);
        board_lock(board_instance);
    }
    board_instance->team_id = -1;
    board_instance->board->clients_connected++;
    board_unlock(board_instance);
    return (board_instance);
}