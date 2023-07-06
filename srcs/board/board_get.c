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

static void touch(const char *path)
{
    int fd = open(path, O_CREAT, 0644);
    if (fd == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "touch",
            "could not create/open file " C_BOLD "(" C_YELLOW "%s" C_RESET "): %s",
            path,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    close(fd);
}

board_instance_t *board_get(bool_t allow_creation)
{
    touch(IPC_PATH);
    key_t key = ftok(IPC_PATH, IPC_KEY);
    if (key == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "open_board",
            "could not get key " C_BOLD "(" IPC_PATH ":%#x)" C_RESET ": %s",
            IPC_KEY,
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
    board_instance_t *board_instance;
    int sem_id = semget(key, 1, 0);
    if (sem_id == -1 && !allow_creation)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "open_board",
            "Board does not exist, and creation is not allowed");
        exit(EXIT_FAILURE);
    }
    else if (sem_id == -1)
    {
        ft_log(
            LOG_LEVEL_INFO,
            "open_board",
            "Board does not exist, creating it...");
        board_instance = board_create(key);
    } else {
        ft_log(
            LOG_LEVEL_INFO,
            "open_board",
            "Board exists, opening it...");
        board_instance = board_open(key);
        board_lock(board_instance);
    }
    board_instance->player.player_id = PLAYER_NO_ID;
    board_instance->player.team_id = PLAYER_NO_ID;
    board_instance->board->clients_connected++;
    board_unlock(board_instance);
    return (board_instance);
}