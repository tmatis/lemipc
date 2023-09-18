#include <board.h>
#include <ft_string.h>
#include <bool_t.h>
#include <unistd.h>
#include <pawn.h>
#include <ft_printf.h>
#include <ft_logs.h>
#include <signal.h>
#include <msgbox.h>
#include <game.h>
#include <utils_lemipc.h>
#include <sys/types.h>

/**
 * @brief Called when ctrl+c is pressed
 * 
 * @param signo
 */
static void sig_handler(int signo)
{
	(void)signo;
	ft_printf("\e[2K\r"); // erase the line
	force_stop();
}

/**
 * @brief Set the up signals
 * 
 */
static void setup_signals(void)
{
	signal(SIGINT, sig_handler);
}

int main(int argc, char **argv)
{
	if (argc < 4 || argc > 5)
	{
		ft_log(
			LOG_LEVEL_INFO,
			"usage: "
			C_BOLD "%s" C_RESET " "
			C_UNDERLINE "arena_size" C_RESET " "
			C_UNDERLINE "team_nb" C_RESET " "
			C_UNDERLINE "minimum_players" C_RESET " "
			"[speed]" C_RESET,
			argv[0]);
		exit(EXIT_FAILURE);
	}
	int arena_size = ft_atoi(argv[1]);
	int team_nb = ft_atoi(argv[2]);
	int minimum_players = ft_atoi(argv[3]);
	int speed = DEFAULT_SPEED;
	if (argc == 5)
		speed = ft_atoi(argv[4]);
	if (arena_size <= 0 || team_nb <= 0 || minimum_players <= 0 || speed <= 0)
	{
		ft_log(
			LOG_LEVEL_ERROR,
			"arena_size, team_nb, minimum_players and speed must be positive integers");
		exit(EXIT_FAILURE);
	}
	board_instance_t *board_instance = board_get(true, arena_size);
	board_instance->team_id = team_nb;
	if (pawn_join_board(board_instance))
		ft_log(LOG_LEVEL_FATAL, "could not join board");
	else
	{
		setup_signals();
		game_routine(board_instance, minimum_players, speed);
	}
	board_disconnect(board_instance);
	return (0);
}