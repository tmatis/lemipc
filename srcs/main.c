#include <board.h>
#include <ft_string.h>
#include <bool_t.h>
#include <unistd.h>
#include <pawn.h>
#include <ft_printf.h>
#include <ft_logs.h>

static void hang(void)
{
	char c;
	ft_log(LOG_LEVEL_DEBUG, "hang", "press enter to continue...");
	read(STDIN_FILENO, &c, 1);
}

int main(int argc, char **argv)
{
	bool_t is_graphic_mode = argc == 2 && ft_strcmp(argv[1], "-g") == 0;
	board_instance_t *board_instance = board_get(!is_graphic_mode);
	if (pawn_join_board(board_instance))
	{
		ft_log(LOG_LEVEL_FATAL, "main", "could not join board");
		board_disconnect(board_instance);
	}
	hang();
	board_disconnect(board_instance);
	return (0);
}