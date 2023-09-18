#include <board.h>
#include <pawn.h>
#include <ft_printf.h>
#include <utils_lemipc.h>
#include <ft_logs.h>

#define WAIT_100MS 100000

static void text_render_board(board_instance_t *board_instance)
{
    int board_size = board_instance->board->board_size;
    for (int x = 0; x < board_size; x++)
    {
        for (int y = 0; y < board_size; y++)
        {
            int *cell = pawn_get(board_instance, x, y);
            if (*cell == EMPTY_CELL)
                ft_printf(" ");
            else
                ft_printf("%i", *cell);
        }
        ft_printf("\n");
    }
}

void text_visualizer_launch(board_instance_t *board_instance)
{
    while (true)
    {
        board_lock(board_instance);
        if (force_stop_is_set())
        {
            ft_log(
                LOG_LEVEL_INFO,
                "forced stop, leaving the board");
            board_unlock(board_instance);
            return;
        }
        ft_printf("\033c");
        ft_printf("Clients connected: %i\n", board_instance->board->clients_connected);
        ft_printf("Players on board: %i\n", board_instance->board->players_on_board);
        ft_printf(
            "Game status: %s\n",
            board_instance->board->game_state == GAME_IDLE ? "idle" : "running");
        if (board_instance->board->game_result == DRAW_RESULT)
            ft_printf("Draw\n");
        else if (board_instance->board->game_result != NO_RESULT)
            ft_printf("Winner: team %i\n", board_instance->board->game_result);
        text_render_board(board_instance);
        board_unlock(board_instance);
        usleep(WAIT_100MS);
    }
}