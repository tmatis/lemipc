#include <board.h>

/**
 * @brief Return the pawn at the given position
 * 
 * @param board_instance the board instance
 * @param x 
 * @param y 
 * @return int* a pointer to the pawn
 */
int *pawn_get(board_instance_t *board_instance, int x, int y)
{
    return &(board_instance->board->slots[x + y * board_instance->board->board_size]);
}