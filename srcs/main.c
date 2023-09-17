#include <board.h>
#include <ft_string.h>
#include <bool_t.h>
#include <unistd.h>
#include <pawn.h>
#include <ft_printf.h>
#include <ft_logs.h>
#include <graphic_visualizer.h>
#include <signal.h>
#include <msgbox.h>
#include <game.h>

// static void handle_sigint(void)
// {
// 	ft_log(LOG_LEVEL_WARNING, "handle_sigint", "Cannot exit with Ctrl+C");
// }

int main(int argc, char **argv)
{
	// signal(SIGINT, (__sighandler_t)handle_sigint);
	if (argc < 4)
	{
		ft_log(
			LOG_LEVEL_INFO,
			"usage: " C_BOLD "%s" C_RESET " "
			C_UNDERLINE "arena_size" C_RESET " "
			C_UNDERLINE "team_nb" C_RESET " "
			C_UNDERLINE "minimum_players" C_RESET " "
			C_ITALIC "[-g]" C_RESET,
			argv[0]);
		exit(EXIT_FAILURE);
	}
	int arena_size = ft_atoi(argv[1]);
	int team_nb = ft_atoi(argv[2]);
	int minimum_players = ft_atoi(argv[3]);
	if (arena_size <= 0 || team_nb <= 0 || minimum_players <= 0)
	{
		ft_log(
			LOG_LEVEL_ERROR,
			"arena_size, team_nb and minimum_players must be positive integers");
		exit(EXIT_FAILURE);
	}
	bool_t is_graphic_mode = argc == 5 && !ft_strcmp(argv[4], "-g");
	board_instance_t *board_instance = board_get(!is_graphic_mode, arena_size);
	board_instance->team_id = team_nb;
	if (is_graphic_mode)
	{
		ft_log(LOG_LEVEL_INFO, "starting graphic mode");
		visualizer_launch(board_instance);
	}
	else
	{
		if (pawn_join_board(board_instance))
			ft_log(LOG_LEVEL_FATAL, "could not join board");
		else
			game_routine(board_instance, minimum_players);
	}
	board_disconnect(board_instance);
	return (0);
}