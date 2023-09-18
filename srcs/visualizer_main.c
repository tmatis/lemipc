#include <graphic_visualizer.h>
#include <stdlib.h>
#include <ft_logs.h>
#include <ft_string.h>
#include <signal.h>
#include <utils_lemipc.h>
#include <ft_printf.h>

static void sig_handler(int signo)
{
	(void)signo;
	ft_printf("\e[2K\r"); // erase the line
	force_stop();
}

static void setup_signals(void)
{
	signal(SIGINT, sig_handler);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_log(
            LOG_LEVEL_INFO,
            "usage: " C_BOLD "%s" C_RESET " " C_UNDERLINE "board_size" C_RESET " ",
            argv[0]);
        exit(EXIT_FAILURE);
    }
    int arena_size = ft_atoi(argv[1]);
    if (arena_size <= 0)
    {
        ft_log(
            LOG_LEVEL_ERROR,
            "arena_size must be a positive integer");
        exit(EXIT_FAILURE);
    }
    board_instance_t *board_instance = board_get(false, arena_size);
    ft_log(
        LOG_LEVEL_INFO,
        "launching visualizer");
    setup_signals();
    visualizer_launch(board_instance);
    board_disconnect(board_instance);
    return (0);
}