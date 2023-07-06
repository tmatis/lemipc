#include <board.h>
#include <ft_string.h>
#include <bool_t.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char c;
	bool_t is_graphic_mode = argc == 2 && ft_strcmp(argv[1], "-g") == 0;
	board_instance_t *board_instance = board_get(!is_graphic_mode);
	read(0, &c, 1);
	board_disconnect(board_instance);
	return (0);
}