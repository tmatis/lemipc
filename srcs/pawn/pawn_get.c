#include <board.h>

player_t *pawn_get(board_instance_t *board_instance, int x, int y)
{
    return &(board_instance->board->slots[x + y * board_instance->board->board_size]);
}