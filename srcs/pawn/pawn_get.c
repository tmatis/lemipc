#include <board.h>

player_t pawn_get(board_instance_t *board_instance, uint8_t x, uint8_t y)
{
    return (board_instance->board->slots[x + y * BOARD_SIZE]);
}